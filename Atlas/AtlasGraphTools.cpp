#include "AtlasGraphTools.hpp"

/***********************************************************
 ************************************************************
 ** Constructor for Node Type without parent graph.
 ** Arguments are x and y position of node in cartesian space
 ************************************************************
 ************************************************************/
namespace Atlas {
Node::Node(float x, float y)
{
    this->nodeID = -1;
    this->location.x = x;
    this->location.y = y;
    this->neighborCount = 0;
    this->neighbors = new PriorityQueue(this);
    this->pathLength = INFINITY;
    this->neighborsHeuristic = (PriorityQueue*)NULL;
}


/***********************************************************
 ************************************************************
 ** Function to add a neighbor to a node
 ** A neighbor is defined as a node that
 ** can be reached from this node
 ** Argument is the node to be added and distance to neightbor
 ** Special Return Codes:
 **       -2: Indicated nodes are already neighbors
 ************************************************************
 ************************************************************/

int Node::addNeighbor(Node *neighbor)
{
    if (neighbor == (Node *)NULL)
    {
        return NULL_ARG;
    }

    if (this->isNeighbor(neighbor)) {
        return -2;
    }

    int rc1 = this->neighbors->insert(neighbor, 0);
    int rc2 = neighbor->neighbors->insert(this, 0);
    this->neighborCount++;
    neighbor->neighborCount++;
    return (rc1&rc2);

}

/***********************************************************
************************************************************
** Function to get neighbor nodes sorted by
** the worst next node first
** A neighbor is defined as a node that
** can be reached from this node
** Argument is the goal node to be reached
** No Special Return Coddes
************************************************************
************************************************************/

PriorityQueue* Node::getNeighbors(Node* goalNode) {
    if (goalNode == (Node*)NULL) {
        return (PriorityQueue*)NULL_ARG;
    }
    PriorityQueue *queue = new PriorityQueue(goalNode);
    int i;
    for (i = 0; i < this->getNeighbors()->getNodeCount(); i++) {

        queue->insert(this->neighbors->getNodeAtIndex(i), this->pathLength + getNodeDistance(this, this->neighbors->getNodeAtIndex(i)));
    }
    return queue;

}

/***********************************************************
************************************************************
** Function to reset the neighbor hueristic queue
** No Special Return Codes
************************************************************
************************************************************/

int Node::resetNeighbors() {
    this->neighborsHeuristic = (PriorityQueue*)NULL;
    return SUCCESS;

}


/***********************************************************
 ************************************************************
 ** Function to get the distance between two nodes
 ** Argument is two node pointers
 ** inlined to reduce function call overhead
 ** Special Return Codes: None
 ************************************************************
 ************************************************************/

float getNodeDistance(Node *node1, Node *node2)
{
    if (node1 == (Node *)NULL || node2 == (Node *)NULL)
    {
        return NULL_ARG;
    }

    return sqrt((node1->getLocation().x - node2->getLocation().x) *
                    (node1->getLocation().x - node2->getLocation().x) +
                (node1->getLocation().y - node2->getLocation().y) *
                    (node1->getLocation().y - node2->getLocation().y));
}

/***********************************************************
 ************************************************************
 ** Function to check if a node neighbors another node
 ** A neighbor is defined as a node that
 ** can be reached from this node
 ** Argument is potential neighbor
 ** Special Return Codes: None
 ************************************************************
 ************************************************************/

int Node::isNeighbor(Node *node)
{
    if (node == (Node *)NULL)
    {
        return NULL_ARG;
    }
    return (this->neighbors->getNodeIndex(node) != -1);
}

/***********************************************************
 ************************************************************
 ** Constructor for PriorityQueue Type
 ** Arguments is the goal node to be reached in this queue
 ************************************************************
 ************************************************************/

PriorityQueue::PriorityQueue(Node *goalNode) {
    this->goalNode = goalNode;
    this->count = 0;
}

/***********************************************************
 ************************************************************
 ** Function implementation for GetNodeIndex
 ** Takes node to be indexed
 ** Returns -1 if the node is not in the queue
 ************************************************************
 ************************************************************/

int PriorityQueue::getNodeIndex(Node *node)
{
    if (node == (Node *)NULL) //Check for null input argument
    {
        return NULL_ARG;
    }

    int i;

    for (i = 0; i < this->count; i++)
    {
        if (node == this->nodes[i])
        {
            return i;
        }
    }

    return -1;
}

/***********************************************************
 ************************************************************
 ** Function implementation for GetNodeAtIndex
 ** Takes the node index
 ** No special return codes
 ************************************************************
 ************************************************************/

Node* PriorityQueue::getNodeAtIndex(int index) const {
   if(index < this->count)
   return this->nodes[index];
   else {
       return (Node*)OUT_OF_BOUNDS;
   }
}

/***********************************************************
 ************************************************************
 ** Function implementation for getHeuristicAtIndex
 ** Takes the index
 ** No special return codes
 ************************************************************
 ************************************************************/

float PriorityQueue::getHeuristicAtIndex(int index) const {
   if(index < this->count)
   return this->heuristics[index];
   else {
       return OUT_OF_BOUNDS;
   }
}

/***********************************************************
 ************************************************************
 ** Function implementation for Insert
 ** Takes node to be added into queue
 ** Returns -2 if the node is already in the queue in a better path
 ************************************************************
 ************************************************************/

int PriorityQueue::insert(Node *node, float pathLength)
{
    if (node == (Node *)NULL) //Check for null input argument
    {
        return NULL_ARG;
    }

    //
    //  Calculate the remaining distance to the goal node
    //

    float remainingDistance = getNodeDistance(node, this->goalNode);
    float newHeuristic = (SHORTEST_PATH_BIAS * pathLength) + (CLOSEST_NODE_BIAS * remainingDistance);

    //
    // Check and see if the node exists in the queue
    //

    int nodeIndex = this->getNodeIndex(node);

    //
    // This path is taken if the if the node is in the queue
    //

    if (nodeIndex != -1)
    {
        if (newHeuristic > this->heuristics[nodeIndex])
        {
            //
            // Node has already been visited with a shorter path. No action necesary.
            //

            return -2;
        }
        else
        {
            this->removeNode(nodeIndex);
        }
    }

    int index;
    int insertIndex = this->count;

    this->nodes.resize(this->count+1);
    this->heuristics.resize(this->count+1);

    for (index = 0; index < this->count; index++)
    {
        if (newHeuristic > heuristics[index])
        {
            insertIndex = index;
            break;
        }
    }

    for (index = this->count - 1; index >= insertIndex; index--)
    {
        this->nodes[index + 1] = this->nodes[index];
        this->heuristics[index + 1] = this->heuristics[index];
    }

    this->nodes[insertIndex] = node;
    this->heuristics[insertIndex] = newHeuristic;
    this->count++;
    return SUCCESS;
}

/***********************************************************
************************************************************
** Function implementation for Remove of a PriorityQueue
** Takes idex of node to be removed
** No speical return codes
************************************************************
************************************************************/

int PriorityQueue::removeNode(int index) {
    if (index >= count) {
        return OUT_OF_BOUNDS;
    }
    for (; index + 1 < count; index++) {
        this->nodes[index] = this->nodes[index+1];
        this->heuristics[index] = this->heuristics[index+1];
    }
    this->count--;
    return SUCCESS;
}

/***********************************************************
************************************************************
** Function implementation for Remove of a PriorityQueue
** Takes the node to be removed
** Returns -1 if the node is not in the array
************************************************************
************************************************************/

int PriorityQueue::removeNode(Node* node) {
    if (node == (Node*) NULL) {
        return NULL_ARG;
    }
    int index = this->getNodeIndex(node);
    if (index == -1) {
        return -1;
    }
    return this->removeNode(index);
}

/***********************************************************
************************************************************
** Function implementation for GetMin of a PriorityQueue
**  Returns the node at the end of the queue
************************************************************
************************************************************/

Node* PriorityQueue::getMin() {
    if (this->count == 0) {
        return (Node*)OUT_OF_BOUNDS;
    }
    return this->getNodeAtIndex(this->count-1);;
}

/***********************************************************
************************************************************
** Function implementation for Pop of a PriorityQueue
**  Returns the node at the end of the queue
************************************************************
************************************************************/

Node* PriorityQueue::pop() {
    if (this->count == 0) {
        return (Node*)OUT_OF_BOUNDS;
    }
    Node* retNode = this->getMin();
    this->count--;
    return retNode;
}

/***********************************************************
************************************************************
** Function implementation for AStar
**  Arguments are starting node and path queue
** Returns a -1 if a path does not exist between nodes
************************************************************
************************************************************/

int AStar(Node* startNode, Node* goalNode) {
    if (startNode == (Node*)NULL || goalNode == (Node*)NULL) {
        return NULL_ARG;
    }
    PriorityQueue *queue = new PriorityQueue(goalNode);
    startNode->pathLength = 0;
    queue->insert(startNode, 0);
    float rc;
    int i, deadPath;
    deadPath = 0;
    while (deadPath == 0) {
        for (i = 0; i < queue->getNodeCount(); i++) {
            if (queue->getHeuristicAtIndex(i) != INFINITY) {
                deadPath = 0;
                break;
            }
            else {

                deadPath = 1;
            }
        }
        if (deadPath == 1) {
            break;
        }
        Node* currentNode = queue->getMin();
        if (currentNode->neighborsHeuristic == (PriorityQueue*)NULL) {
            currentNode->neighborsHeuristic = currentNode->getNeighbors(goalNode);
        }
        if (currentNode->neighborsHeuristic->getNodeCount() == 0) {
            queue->removeNode(currentNode);
            currentNode->pathLength = INFINITY;
            queue->insert(currentNode, INFINITY);
            continue;
        }

        Node* nextNode = currentNode->neighborsHeuristic->pop();

        if (nextNode == goalNode) {
            goalNode->previous = currentNode;
            std::cout << "I AM HERE" << std::endl;
            break;
            //return SUCCESS;
        }

        rc = queue->insert(nextNode, currentNode->pathLength + getNodeDistance(currentNode, nextNode));
        if (rc == -2) {
            queue->removeNode(currentNode);
            currentNode->pathLength = INFINITY;
            queue->insert(currentNode, INFINITY);
        }
        else if (rc == SUCCESS) {
            nextNode->pathLength = currentNode->pathLength + getNodeDistance(currentNode, nextNode);
            nextNode->previous = currentNode;
        }
    }
    std::cout << "H" << std::endl;
    for (i = 0; i < queue->getNodeCount(); i++) {
        std::cout << queue->getHeuristicAtIndex(i) << std::endl;
        if (queue->getHeuristicAtIndex(i) != INFINITY) {
            std::cout << "(" << queue->getNodeAtIndex(i)->getLocation().x << "," << queue->getNodeAtIndex(i)->getLocation().y << ")" << std::endl;
        }
        queue->getNodeAtIndex(i)->resetNeighbors();
    }

    if (goalNode->previous != (Node*)NULL) {
        return SUCCESS;
    }

    return -1;
}
}

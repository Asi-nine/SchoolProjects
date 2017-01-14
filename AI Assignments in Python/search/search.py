# search.py
# ---------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

"""
In search.py, you will implement generic search algorithms which are called 
by Pacman agents (in searchAgents.py).
"""

import util

######## Parts filled in by Peter Valovcik, CS3346

class SearchProblem:
  """
  This class outlines the structure of a search problem, but doesn't implement
  any of the methods (in object-oriented terminology: an abstract class).
  
  You do not need to change anything in this class, ever.
  """
  
  def getStartState(self):
     """
     Returns the start state for the search problem 
     """
     util.raiseNotDefined()
    
  def isGoalState(self, state):
     """
       state: Search state
    
     Returns True if and only if the state is a valid goal state
     """
     util.raiseNotDefined()

  def getSuccessors(self, state):
     """
       state: Search state
     
     For a given state, this should return a list of triples, 
     (successor, action, stepCost), where 'successor' is a 
     successor to the current state, 'action' is the action
     required to get there, and 'stepCost' is the incremental 
     cost of expanding to that successor
     """
     util.raiseNotDefined()

  def getCostOfActions(self, actions):
     """
      actions: A list of actions to take
 
     This method returns the total cost of a particular sequence of actions.  The sequence must
     be composed of legal moves
     """
     util.raiseNotDefined()
           

def tinyMazeSearch(problem):
  """
  Returns a sequence of moves that solves tinyMaze.  For any other
  maze, the sequence of moves will be incorrect, so only use this for tinyMaze
  """
  from game import Directions
  s = Directions.SOUTH
  w = Directions.WEST
  return  [s,s,w,s,w,w,s,w]

def depthFirstSearch(problem):
  """
  Search the deepest nodes in the search tree first [p 85].
  
  Your search algorithm needs to return a list of actions that reaches
  the goal.  Make sure to implement a graph search algorithm [Fig. 3.7].
  
  To get started, you might want to try some of these simple commands to
  understand the search problem that is being passed in:
  
  print "Start:", problem.getStartState()
  print "Is the start a goal?", problem.isGoalState(problem.getStartState())
  print "Start's successors:", problem.getSuccessors(problem.getStartState())
  """
  "*** YOUR CODE HERE ***"

  #set up the data structure for the fringe and a list to hold explored nodes
  #Stack is appropriate for BFS because it is LIFO
  fringe = util.Stack()
  exploredStates = []

  #set up a node with the position (state), direction (stop for the first node) and stepcost (0 here)
  node = [problem.getStartState(), 'Stop', 0]
  #push the starting node onto the stack
  fringe.push([node])

  #while the fringe contains nodes, keep popping nodes, keeping track of explored positions and checking for goal state
  while not fringe.isEmpty():

    #pop a node off of the stack
    nodePath = fringe.pop()
    
    #get the state of the popped node
    state = nodePath[len(nodePath)-1]
    state = state[0]

    #check to see if the popped node is the goal
    if problem.isGoalState(state):
      #if it is the goal, return the list of the elements of the node list at postion 1, which is a list of directions in this case
      #ignores position 0 because it is the starting position
      return [x[1] for x in nodePath][1:]

    #appends the position of the current nodes to the set of explores states if it is not already in the list
    if state not in exploredStates:
      exploredStates.append(state)

        #loop through all of the successors of the node
      for successor in problem.getSuccessors(state):
          
        #if the state of the successor has not been explored already
        if successor[0] not in exploredStates:
          #make a path that is the current path taken with the successor appended onto it
          successorPath = nodePath[:]
          successorPath.append(successor)
          #push that path of nodes onto the stack
          fringe.push(successorPath)

  #return an empty list if no solution was found
  return []

def breadthFirstSearch(problem):
  "Search the shallowest nodes in the search tree first. [p 81]"
  "*** YOUR CODE HERE ***"
  #set up the data structure for the fringe and a list to hold explored nodes
  #a Priority queue with a function set to length of the queue is appropraite since it will prioritize nodes of equal depth equally
  fringe = util.PriorityQueueWithFunction(len)
  exploredStates = []

  #set up a node with the position (state), direction (stop for the first node) and stepcost (0 here)
  node = [problem.getStartState(), 'Stop', 0]
  #push the stating node onto the queue
  fringe.push([node])

  #while the fringe contains nodes, keep popping nodes, keeping track of explored positions and checking for goal state
  while not fringe.isEmpty():

    #pop a node off of the queue
    nodePath = fringe.pop()
    
    #get the state of the popped node
    state = nodePath[len(nodePath)-1]
    state = state[0]

    #check to see if the popped node is the goal
    if problem.isGoalState(state):
      #if it is the goal, return the list of the elements of the node list at postion 1, which is a list of directions in this case
      #ignores position 0 because it is the starting position
      return [x[1] for x in nodePath][1:]

    #appends the position of the current nodes to the set of explored states if it is not already in the list
    if state not in exploredStates:
      exploredStates.append(state)

        #loop through all of the successors of the node
      for successor in problem.getSuccessors(state):
          
        #if the state of the successor has not been explored already
        if successor[0] not in exploredStates:
          #make a path that is the current path taken with the successor appended onto it
          successorPath = nodePath[:]
          successorPath.append(successor)
          #push that path of nodes onto the queue
          fringe.push(successorPath)

  #return an empty list if no solution was found
  return []
      
def uniformCostSearch(problem):
  "Search the node of least total cost first. "
  "*** YOUR CODE HERE ***"
  #make a cost function by calling getCostOfActions on a path
  def uniformCost (path): 
    #get the cost of the full path
    cost = problem.getCostOfActions([x[1] for x in path])

    return cost

  #set up the data structure for the fringe and a list to hold explored nodes
  #a Priority queue with a function set to cost is appropriate here
  fringe = util.PriorityQueueWithFunction(uniformCost)
  exploredStates = []

  #set up a node with the position (state), direction (stop for the first node) and stepcost (0 here)
  node = [problem.getStartState(), 'Stop', 0]
  #push the starting node into the queue
  fringe.push([node])

  #while the fringe contains nodes, keep popping nodes, keeping track of explored positions and checking for goal state
  while not fringe.isEmpty():

    #pop a node off of the queue
    nodePath = fringe.pop()
    
    #get the state of the popped node
    state = nodePath[len(nodePath)-1]
    state = state[0]

    #check to see if the popped node is the goal
    if problem.isGoalState(state):
      #if it is the goal, return the list of the elements of the node list at postion 1, which is a list of directions in this case
      #ignores position 0 because it is the starting position
      return [x[1] for x in nodePath][1:]

    #appends the position of the current nodes to the set of explored states if it is not already in the list
    if state not in exploredStates:
      exploredStates.append(state)

        #loop through all of the successors of the node
      for successor in problem.getSuccessors(state):
          
        #if the state of the successor has not been explored already
        if successor[0] not in exploredStates:
          #make a path that is the current path taken with the successor appended onto it
          successorPath = nodePath[:]
          successorPath.append(successor)
          #push that path of nodes onto the queue
          fringe.push(successorPath)

  #return an empty list if no solution was found
  return []

def nullHeuristic(state, problem=None):
  """
  A heuristic function estimates the cost from the current state to the nearest
  goal in the provided SearchProblem.  This heuristic is trivial.
  """
  return 0

def aStarSearch(problem, heuristic=nullHeuristic):
  "Search the node that has the lowest combined cost and heuristic first."
  "*** YOUR CODE HERE ***"
  #make a cost function by calling getCostOfActions on a path and adding the heuristic to it
  def costWithHeuristic(path): 
    #get the cost of the full path
    cost = problem.getCostOfActions([x[1] for x in path])
    
    #get the state of the node at the end of the queue
    state = path[len(path)-1]
    state = state[0]

    #set up a call for heuristics to get a heuristic value based on the position at the end of the path for the problem
    heuristicValue = heuristic(state, problem)

    # essentially doing f() = g() + h(), adding path cost and heuristic value
    cost = cost + heuristicValue

    return cost 

  #set up the data structure for the fringe and a list to hold explored nodes
  #a Priority queue with a function set to cost is the heuristic incorporated in is appropriate here
  fringe = util.PriorityQueueWithFunction(costWithHeuristic)
  exploredStates = []

  #set up a node with the position (state), direction (stop for the first node) and stepcost (0 here)
  node = [problem.getStartState(), 'Stop', 0]
  #push the stating node onto the queue.
  fringe.push([node])

  #while the fringe contains nodes, keep popping nodes, keeping track of explored positions and checking for goal state
  while not fringe.isEmpty():

    #pop a node off of the queue
    nodePath = fringe.pop()
    
    #get the state of the popped node
    state = nodePath[len(nodePath)-1]
    state = state[0]

    #check to see if the popped node is the goal
    if problem.isGoalState(state):
      #if it is the goal, return the list of the elements of the node list at postion 1, which is a list of directions in this case
      #ignores position 0 because it is the starting position
      return [x[1] for x in nodePath][1:]

    #appends the position of the current nodes to the set of explored states if it is not already in the list
    if state not in exploredStates:
      exploredStates.append(state)

        #loop through all of the successors of the node
      for successor in problem.getSuccessors(state):
          
        #if the state of the successor has not been explored already
        if successor[0] not in exploredStates:
          #make a path that is the current path taken with the successor appended onto it
          successorPath = nodePath[:]
          successorPath.append(successor)
          #push that path of nodes onto the queue
          fringe.push(successorPath)

  #return an empty list if no solution was found
  return []    
  
# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
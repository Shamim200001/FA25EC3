# Developer Log

## Date: 12/08/25
### Initial Setup
- Forked the project and then cloned to Clion 
- went over the requirements from README
- Started setting up the main.cpp, tree.h, and CMakeLists.txt
- I did some reseach about the OpenAI and how it works

## Date: 12/08/25
### Started on main file
- Implemented Node template class with:
    - String ID field
    - Templated data field
    - Vectors for children and parent pointers
- Started Tree template class implementation:
    - Added root pointer and nodeMap
    - Implemented createRoot() method
    - Created basic destructor structure

### Issues Encountered:
1. I wasn't sure how to handle multiple parents pointing to same child which was new to me and I had to learn it.

### Solutions:
- Used reference counting approach via parent tracking

## Date: 12/09/25
### Tree Class Implementation 
- Completed addNode() method:
- Implemented findNode() using nodeMap
- Created printAll() method:
- finished the tree.h and everything looked good


## Date: 12/10/25
### Main.cpp 
- Updated main.cpp to use the tree class methods
- Fixed story parsing to handle edge cases
- Implemented playGame() method:
- Added proper destructor:
- Tested with sample story structures
- Fixed memory leaks using Valgrind but got broken again.
- Added comments
- Tested with OpenAI API integration and failed
- Added input sanitization in gameplay



## Files Modified:
1. main.cpp 
2. tree.h 
3. CMakeLists.txt
4. developer_log.md - This development log

## Known Issues:
1. I runned the program perfectly but out of nowhere I failed runnning the code 
2. Memory leaks with shared children nodes
3. the output got all missed up

## I forgot to push commit every time I finished with the task but I worked on for the past 3 days and right before turning i retouched the code everything got missed up
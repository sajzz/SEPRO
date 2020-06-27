# SEPRO
exclusively for SE PROJECT

main(10).c:-
  1)file handling is left(reading from file).
  2)dijkstra will return shoterst distance in djDis variable
      and shortest path is stored in pathDJK[] array;
  3)source node must start from "0"
  
  

  Two types of nodes :- Intersection and Destinations
  Nodes named as integers
  
  Admin part functionalities(admin.h):
            1. Add Node
            2. Add Edge and weight
            3. File handling
            4. Calculate Shortest path(Dijkstra Algo.) -> returns shortest path(ex. 1,2,3,4 if 1 is source and 4 is destination)
            5. Predict velocity (input-> conditions of next node i.e timer,length of traffic,avg. speed of traffic)
            
  User part functionalities(user.h)
            1. Select source and destination
            2. Show destinations(prints all "destination" type of nodes )
            



changes made in code 
1) added weightDKJ[] array to get weight of nodes in shortest path.
2) index variable to get total no. of nodes in shortest path.(in case to use in for loop,etc.)



dated:-27 Jun 2020,(14:42)
Aman and Shantanu, yours 3 functions are added and errors are solved,Now a run of complete code is required.

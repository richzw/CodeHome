# tree tranverse 
   
 # wrong version
 def traverse_wrong(node):          
     if isinstance(node, list):     
         for sub_node in node:       
             traverse_wrong(sub_node)    #it only create another generator, not invoke it.
     else:                            
         yield node                  
   
 # right version: 
 def traverse_right(node):            
     if isinstance(node, list):      
         for sub_node in node:      
             for sub_result in traverse_right(sub_node): # another coroutine tranverse the nodes
                 yield sub_result                        # current coroutine just convey the result of coroutine 
     else:                           
         yield node                  
   
 # Python3.3
 def traverse_right2(node):           
     if isinstance(node, list):      
         for sub_node in node:        
             yield from traverse_right2(sub_node)    
     else:                           
         yield node                   
   
 tree = [[[1,2],[3,4]],[[5,6,7],[8,9],[10]]] 
   
 print(list(traverse_wrong(tree)))   # [] 
 print(list(traverse_right(tree)))   # [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] 
 print(list(traverse_right2(tree)))  # [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

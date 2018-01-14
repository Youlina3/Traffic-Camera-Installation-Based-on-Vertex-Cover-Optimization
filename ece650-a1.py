#!/usr/bin/env python

import sys
import re
import intersect
# -*- coding: utf-8 -*

# YOUR CODE GOES HERE

#parser
  

##delete space
def parse_skipspace(out_list, line, index):
    while index < len(line) and line[index].isspace(): 
        index += 1
    return index
    
def parse_cmd(out_list, line, index):
    index = parse_skipspace(out_list, line, index)
    out_list.append(line[index])  
    if line[index] == 'a' or line[index] == 'c':
        index += 1
       
        if line[index] != " ":
            raise Exception("Error:Lack space")        
        index = parse_str(out_list, line, index )
        index += 1
        if line[index] != " ":
            raise Exception("Error:Lack space")         
        index = parse_vertex(out_list, line, index)
        
        
    elif line[index] == 'r':
        index += 1
        if line[index] != " ":
            raise Exception("Error:Lack space")        
        index = parse_str(out_list, line, index)    
        index = parse_skipspace(out_list, line, index+1)
        if index != len(line):
            raise Exception("Error:More invalid characters")
    elif line[index] == 'g':
        index = parse_skipspace(out_list, line, index+1)
        if index != len(line):
            raise Exception("Error:More invalid characters")    
    else:
        raise Exception("Error: First command character is invalid ")
    
  

def parse_str(out_list, line, index):
    index = parse_skipspace(out_list, line, index+1)
    if( line[index] != '"' ):
 
        raise Exception("Error:Invalid string input(lack left double quatation)")
    index += 1
    mystr = ""
    while index < len(line) and line[index] != '"' :
        mystr = mystr+line[index]
        mystr = mystr.lower()
        index = index + 1
    test = re.compile(r'^[a-zA-Z ]+$')
    if index == len(line):
        raise Exception("Error: Invalid string input(lack right double quatation )")
    
    if re.match(test,mystr):
        out_list += [mystr]
        return index
    else:
        raise Exception("Error: Invalid street name")


def parse_number(out_list, line, index):
    index = parse_skipspace(out_list, line, index)
    if index >= len(line):
        raise Exception("Error:Points are invalid")
    mystr = ""
    if line[index] == '-':
        mystr = "-"
        index += 1
    if  ("0123456789".find(line[index])) < 0 :
        raise Exception("Error:Points are invalid")
    while index < len(line) and "0123456789".find(line[index]) >= 0 :
            mystr = mystr + line[index]
            index += 1
    out_list.append(int(mystr))
    return index

def parse_vertex(out_list, line, index):
    index = parse_skipspace(out_list, line, index)
    if index >= len(line):
        return index
    if ( line[index] == '('):
        index += 1
        index = parse_number(out_list, line, index)
        index = parse_skipspace(out_list, line, index)
        if index < len(line) and line[index] == ",":
            index += 1
        else:
            raise Exception("Error: Lack ','")
           
        index = parse_number(out_list, line, index)
        index = parse_skipspace(out_list, line, index)
        if  index <len(line) and line[index] == ')':
                index = parse_vertex(out_list, line, index+1)
                return index
        else:
            raise Exception("Error:No right bracket in points")
            
    else:
        raise Exception("Error:No left bracket in points")
       
        
        
        
  
    
    

####
def main():
    #### YOUR MAIN CODE GOES HERE

    #### sample code to read from stdin.
    #### make sure to remove all spurious print statements as required
    #### by the assignment
    db_street = intersect.DB_street()
    while True:
        line = sys.stdin.readline()
        if line == '':
            break
        
        outlist = [] 
        try:
            index = parse_cmd(outlist, line,0)
    
    
            if outlist[0] == 'a':
                plist = []
                index = 2
                while index < len(outlist):
                    
                    p = intersect.Point(outlist[index],outlist[index+1])
                    plist.append(p)
                    index += 2
             
               
                db_street.add(outlist[1],plist )
            if outlist[0] == 'c':
                plist = []
                index = 2
                while index < len(outlist):
                    p = intersect.Point(outlist[index],outlist[index+1])
                    plist.append(p)
                    index += 2
                db_street.change(outlist[1],plist)
            if outlist[0] == 'r':
                db_street.remove(outlist[1])
             
            if outlist[0] == 'g':
                db_street.generate_graph()
        except Exception as ex:
            print ex
            continue
        sys.stdout.flush()
    ## return exit code 0 on successful termination
    sys.exit(0)

if __name__ == '__main__':
    main()
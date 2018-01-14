import math
import sys

class Point(object):
    def __init__ (self, x, y):
        self.x = float(x)
        self.y = float(y)
    def __str__ (self):
        if self.x == round(self.x) and self.y == round(self.y):
            return '(' + str(int(self.x)) + ',' + str(int(self.y)) + ')'
        elif self.x == round(self.x) and self.y != round(self.y):
            return '(' + str(int(self.x)) + ',' + str("{0:.2f}".format(self.y)) + ')'
        elif self.x != round(self.x) and self.y == round(self.y):
            return '(' + str("{0:.2f}".format(self.x)) + ',' + str(int(self.y)) + ')'
        elif self.x != round(self.x) and self.y != round(self.y):
            return '(' + str("{0:.2f}".format(self.x)) + ',' + str("{0:.2f}".format(self.y)) + ')'
        else:
            return "Error: never happend"  
    
class Line(object):
    def __init__ (self, src, dst):
        self.src = src
        self.dst = dst

    def __str__(self):
        return str(self.src) + '-->' + str(self.dst)

    
def intersect(l1, l2):
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y
    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y
    
    x_list1 = [x1,x2]
    x_list2 = [x3,x4]
    x_list1.sort()
    x_list2.sort()    
 
    y_list1 = [y1,y2]
    y_list2 = [y3,y4]
    y_list1.sort()
    y_list2.sort() 
 
    list_x = [x1,x2,x3,x4]
    list_x.sort()
    list_y = [y1,y2,y3,y4]
    list_y.sort()
    
    intersect_list = []
 
    if x1 != x2 and x3 != x4: 
     
        k1 = (y2 - y1)/(x2 - x1)
        k2 = (y4 - y3)/(x4 - x3)
        
        b1 = y1 - k1*x1
        b2 = y3 - k2*x3
    

    
        if k1!=k2 :
        
            xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
            xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
            xcoor =  xnum / xden

            ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
            yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
            ycoor = ynum / yden

            if x_list1[0] <= xcoor <= x_list1[1] and x_list2[0] <= xcoor <= x_list2[1]  and  y_list1[0] <= ycoor <= y_list1[1] and y_list2[0] <= ycoor <= y_list2[1]:
                
                return Point(xcoor, ycoor)

            else:
              
                return 0
            
        else:
       
            if b1 == b2:

                if (x_list1[1] > x_list2[0] and x_list1[0] < x_list2[0]) or (x_list2[1] > x_list1[0] and x_list2[0] < x_list1[0]):
                    intersect_list.append(Point(list_x[1],list_y[1]))
                    intersect_list.append(Point(list_x[2],list_y[2]))
                    return intersect_list

                elif x_list1[1] == x_list2[0]:
                    return Point(list_x[1],list_y[1])
                else:
                    return 0

            else:
                return 0
                
            
                
    
    elif x1 != x2 or x3 != x4:
            xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
            xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
            xcoor =  xnum / xden

            ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
            yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
            ycoor = ynum / yden
          

            if x_list1[0] <= xcoor <= x_list1[1] and x_list2[0] <= xcoor <= x_list2[1]  and  y_list1[0] <= ycoor <= y_list1[1] and y_list2[0] <= ycoor <= y_list2[1]:
                return Point (xcoor, ycoor)
            else:
               
                return 0

    else:
        
        if x1 == x2 == x3 == x4:
            if list_y[1] != list_y[2]:
                intersect_list.append(Point(x1,list_y[1]))
                intersect_list.append(Point(x2,list_y[2]))
                return intersect_list
            else:
                return Point(x1,list_y[1])
        else:
            return 0
               

    
def compare_line(L_list1,L_list2,Ver_o,inter_o):
    for i in range(0,len(L_list1)):
        for j in range(0,len(L_list2)):
            
            result_inter = intersect(L_list1[i],L_list2[j])
            if isinstance(result_inter,Point):
                    Ver_o.append(result_inter)
                    Ver_o.append(L_list1[i].src)
                    Ver_o.append(L_list1[i].dst)
                    Ver_o.append(L_list2[j].src)
                    Ver_o.append(L_list2[j].dst)
                    inter_o.append(result_inter)

                    
            if isinstance(result_inter,list):
                    Ver_o.append(L_list1[i].src)
                    Ver_o.append(L_list1[i].dst)
                    Ver_o.append(L_list2[j].src)
                    Ver_o.append(L_list2[j].dst)
                    Ver_o.append(result_inter[0])
                    Ver_o.append(result_inter[1])
                    inter_o.append(result_inter[0]) 
                    inter_o.append(result_inter[1])

 
 
# determin the point on line segments                  
def distance(p1,p2):
    return math.sqrt((p1.x - p2.x)**2 + (p1.y - p2.y)**2)

def is_between(p1,p3,p2):
    
    if distance(p1,p3) + distance(p3,p2) - distance(p1,p2) < 0.00000000001:
        return  1


#compare points' position
def comp(x, y):
    if x.x == y.x:
        if x.y >= y.y:
            return 1
        else:
            return -1
    if x.x < y.x:
        return -1
    else:
        return 1
    
#line_o is the line segment of each street; inter save the intersects; edg save the final results of edges
def create_edge(line_o, inter,edg):
    inter_list = []                             #save intersects
    point_edg_o = [line_o.src,line_o.dst]       #valid vertices including intersects
    flag = 0
    
    for k in range(len(inter)):        
        if is_between(line_o.src,inter[k],line_o.dst): 
            inter_list.append(inter[k])
            point_edg_o.append(inter[k])
            flag += 1
    # no intersect in that line segment
    if flag == 0:
        return 
    else:

        point_edg_o.sort(comp)
        for m in range(len(point_edg_o)):
            for n in list(reversed(range(m+1,len(point_edg_o)))):
                if point_edg_o[m].x == point_edg_o[n].x and point_edg_o[m].y == point_edg_o[n].y:
                        point_edg_o.pop(n)
        for i in range(len(point_edg_o)-1):
            edg.append(Line(point_edg_o[i],point_edg_o[i+1]))
            i += 1
        return
    

    
    
class DB_street(object):
    def  __init__ (self):
        self.name_array = []
        self.point_array = []
        self.line_db_list = []
        
        
#add street               
##street_name and street_point are arrays

    def add(self, street_name, street_point):
        if street_name in self.name_array:
            raise Exception( "Error:This street has been added ")
        self.name_array.append(street_name)
        self.point_array.append(street_point)
          
        
#remove street
    def remove(self, remove_name):
        self.rmflag = 0
        for i in list(reversed(range(len(self.name_array)))):
            if remove_name == self.name_array[i]:
                self.rmflag = 1
                self.name_array.pop(i)
                self.point_array.pop(i)
                
        if self.rmflag == 0:
            raise Exception("Error:This street name doesn't exit")
        
#change street
    def change(self, change_name, change_point):
        self.flag = 0
        for i in range(0,len(self.name_array)):
            if change_name == self.name_array[i]:
                self.flag = 1
                self.point_array[i] = change_point
                
  
                
        if self.flag == 0:
            raise Exception( "Error:This street name doesn't exit")
        
#generate graph
    def generate_graph(self):
        self.line_list = []
        self.line_db_list = []
        self.inter = []
        self.Ver = []
        self.edg = []        
    #creat line list in DB_street
       
        for i in range(len(self.point_array)):
            self.line_list = []
            for j in range(len(self.point_array[i])-1):
                self.line_list.append(Line(self.point_array[i][j],self.point_array[i][j+1]))
            self.line_db_list.append(self.line_list)
       
       
   #compare line segments of each streets and get some vertices and intersects     
        for i in range(len(self.line_db_list)):
            for j in range(i+1,len(self.line_db_list)):
                compare_line(self.line_db_list[i],self.line_db_list[j],self.Ver,self.inter)
                
    #delete same intersects           
        for m in range(len(self.inter)):
            for n in list(reversed(range(m+1,len(self.inter)))):
                if self.inter[m].x == self.inter[n].x and self.inter[m].y == self.inter[n].y:
                    self.inter.pop(n)
                    
    #delete same vertices    
        for m in range(len(self.Ver)):
            for n in list(reversed(range(m+1,len(self.Ver)))):
                if self.Ver[m].x == self.Ver[n].x and self.Ver[m].y == self.Ver[n].y:
                    self.Ver.pop(n)                   
    #create edge
        for i in range(len(self.line_db_list)):
            for j in range(len(self.line_db_list[i])):
                create_edge(self.line_db_list[i][j], self.inter,self.edg)
                

                
    ###show vertices and edge  
  
        
        print 'V '+ str(len(self.Ver))
        

 
            
        linev1Flag = 0
        linev2Flag = 0
        self.edgesArrayWithIndex = []
        for i in range(0, len(self.edg)):
            for k in range(0, len(self.Ver)):
                    if self.edg[i].src == self.Ver[k]:
                        linev1Flag = 1
                        edgeindex1 = k+1
                    if self.edg[i].dst == self.Ver[k]:
                        linev2Flag = 1
                        edgeindex2 = k+1
            if(linev1Flag == 1 and linev2Flag ==1):
                self.edgesArrayWithIndex.append([str(edgeindex1),str(edgeindex2)])

                
        # sort edgesArrayWithIndex
        for i in range(0, len(self.edgesArrayWithIndex)):
            if int(self.edgesArrayWithIndex[i][0]) > int(self.edgesArrayWithIndex[i][1]):
                self.tmp = self.edgesArrayWithIndex[i][0]
                self.edgesArrayWithIndex[i][0] = self.edgesArrayWithIndex[i][1]
                self.edgesArrayWithIndex[i][1] = self.tmp   
                
        for i in range(0, len(self.edgesArrayWithIndex)):
            self.edgesArrayWithIndex[i][0] = str(int(self.edgesArrayWithIndex[i][0]) - 1)
            self.edgesArrayWithIndex[i][1] = str(int(self.edgesArrayWithIndex[i][1]) - 1)
                    
        
        sys.stdout.write("E {")
        for i in range(0, len(self.edgesArrayWithIndex)-1):
            tmp_str = '<'+str(self.edgesArrayWithIndex[i][0])+','+str(self.edgesArrayWithIndex[i][1])+'>,'
            sys.stdout.write(tmp_str)
        if len(self.edgesArrayWithIndex) != 0:
            i = len(self.edgesArrayWithIndex)-1
            tmp_str = '<'+str(self.edgesArrayWithIndex[i][0])+','+str(self.edgesArrayWithIndex[i][1])+'>'
            sys.stdout.write(tmp_str)
        sys.stdout.write('}\n')        
        
        
        
                   
        
        
        
        
    
    
    

       
    
##if __name__ == '__main__':
        ##p1 = Point (3, 3)
        ##p2 = Point (1, 3)
        ##p3 = Point (2, 3)
        ##p4 = Point (4, 3)
    
        ##l1 = Line (p1, p2)
        ##l2 = Line (p3, p4)
        ##print 'Intersect of', l1, 'with', l2, 'is', intersect(l1, l2)
# processor CSS

This program was writtem as a project for Algorithms and Data Structures course. It is an implementation of simple engine for processing CSS blocks as a console application.  

### Implementation
Selectors and attributes are stored in lists. CSS blocks are stored in doubly linked list of arrays of size T. Those arrays consists of structures representing CSS blocks. For this project I implemented my own doubly linked list with operations of addition and deletion of element.

### Commands
- ???? - beginning of commands' section
- **** - resume reading CSS blocks
- ? - print number of CSS blocks
- i,S,? - print number of selectors of i-th block (numbers starting at 1), if such block does not exsist - skip
- i,A,? - print number of attributes of i-th block, if such block does not exsist - skip
- i,S,j - print j-th selector of i-th block, such block or selector does not exsist - skip
- i,A,n - print value of attribute of name n in i-th block
- n,A,? - print the total (for all blocks) number of occurences of attribute of name n
- z,S,? - print the total (for all blocks) number of occurences of selector of name z
- z,E,n - print value of attribute of name n for z-th block, if there is more than one occurence - print the last one, if such attribute does not exsist - skip
- i,D,* - delete a whole i-th block (with all selectors and attributes), after successful deletion print "deleted"
- i,D,n - delete attribute of name n from i-th block, if after deletion there is an empty block - remove a whole block, after successful deletion print "deleted"

### Example
Input
```
#breadcrumb
{
width: 80%;
font-size: 9pt;
}
h1, body {
min-width: 780px;
margin: 0;
padding: 0;
font-family: "Trebuchet MS", "Lucida Grande", Arial;
font-size: 85%;
color: #666666;
}
h1, h2, h3, h4, h5, h6 {color: #0066CB;}
????
?
1,S,?
1,S,1
1,A,?
2,A,font-family
h1,S,?
color,A,?
h1,E,color
1,A,padding
1,D,*
?
2,D,color
?
****
h1, h2, h3, h4, h5, h6 {color: #0066FF;}
????
?
```

Output
```
? == 3
1,S,? == 1
1,S,1 == #breadcrumb
1,A,? == 2
2,A,font-family == "Trebuchet MS", "Lucida Grande", Arial
h1,S,? == 2
color,A,? == 2
h1,E,color == #0066CB
1,D,* == deleted
? == 2
2,D,color == deleted
? == 1
? == 2
```

Project was realized in March and April 2023

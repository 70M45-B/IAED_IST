/*
iaed-23
File: project1.c
Author: Tomas Bernardino
ID: ist1107052
Description: public transports management system.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
/*used to define the variable state inside a string with quotation marks */
#define IN 1
/*used to define the variable state outside a string with quotation marks */
#define OUT 0 
#define FIRST 0 /*Is used as the first index of a vector*/
#define SEC 1   /*Is used as the second index of a vector*/
#define MAX_STOPS 10000 /*Maximum number of stops*/
#define MAX_S_NAME 50   /*Maximum size of a stop name without the '\0'*/
#define MAX_LINES 200   /*Maximum number of lines*/
#define MAX_STOPS_PER_LINE /*Maximum number of stops per line*/
#define MAX_L_NAME 20   /*Maximum size of a line name without the '\0'*/
#define MAX_LINKS 30000 /*Maximum number of links*/
#define INVERSO_LENGTH 7


/*****************Data types*****************/
/*Data types*/
typedef struct{
    char name[MAX_S_NAME];
    double latitude;
    double longitude;
    int num_lines;
    int count_stop_l;
    char stop_lines[MAX_LINES][MAX_L_NAME];
}stop;


typedef struct {
    char name[MAX_L_NAME];
    stop start_s;
    stop destination_s;
    int num_stops;
    float total_price;
    float total_duration;
    int num_links;
    int count_line_s;
    char all_line_s[MAX_STOPS_PER_LINE][MAX_S_NAME];      
}line;
/********************************************/


/*vector that will store all the stops recieved on the input*/
stop stops[MAX_STOPS];
/*variable that will keep track of the number of stops in the stops vector*/ 
int count_s = 0;

/*vector that will store all the lines recieved on the input*/
line lines[MAX_LINES];
/*variable that will keep track of the number of lines in the lines vector*/ 
int count_l = 0;
/*variable that will keep track of the number of links introduced*/
int count_links = 0;

/****************************************************************************/


/****************Prototypes*****************/

int exists(char name[],int count,char type);

/*stop command*/
void add_list_stops();
void list_stops();
void add_stop(stop s);
void stop_process();
char * read_name(char character);

/*line command*/
void read_line();
void list_lines();
void add_line(line r, char word[]);
int is_inverso(char word[]);

/*link command*/
void read_link();

/*intersections command*/
void list_intersections();
void sort_(int index);
/*******************************************/


int main()
{   
    /*variable that reads the character corresponding to the command 
    (from stdin)*/
    char c;
    while((c = getchar())!='q')
    {
        switch (c)
        {
        case 'p':
            add_list_stops();
            break;
        case 'c':
            read_line();
            break;
        case 'l':
            read_link();
            break;
        case 'i':
            list_intersections();
            break;
        default:
            break;
        }  
    }
    return 0;
}


/*
Searches for a name in the stops or lines vector by comparing the name recieved
on the input with each stop or line name of the vector, depending on the type 
and count variables recieved on the input. 
Returns the index of the name in the vector if found, else returns -1.
*/
int exists(char name[], int count,char type)
{   int i;
    for(i = 0; i < count;i++){
        if(type == 's')
        {
            if((strcmp(name,stops[i].name)) == 0)
            return i;
        }
        else if( type == 'l')
        {
            if((strcmp(name,lines[i].name)) == 0)
            return i;
        }
    }
    return -1;
}

/*Insertion sort:
-recieves the index to access the correspondent stop in the stops vector;
Beginning on the second element (i = 1) of the strings vector and so on, this 
function will store the 'i' value of the vector in a temporary variable (temp)
in order to compare it to the ones on the left, if any elements are larger than
what is in temp, this function will shift those elements to the right. 
If the element is less than temp, or it runs out of elements to compare, 
it stops and copies the value of temp to the open spot */
void sort_(int index)
{
    int i,j;
    char temp[MAX_L_NAME]; /*temporary variable*/
    for(i = 1; i < stops[index].count_stop_l; i++)
    {
        strcpy(temp,stops[index].stop_lines[i]);
        j = i-1;

        while(j >= 0 && strcmp(stops[index].stop_lines[j],temp) > 0)
        {
           strcpy(stops[index].stop_lines[j + 1],stops[index].stop_lines[j]);
           j--;
        }
        strcpy(stops[index].stop_lines[j + 1],temp);
    }
}


/*
This function only task is to print all the lines that go through each stop 
(if that value is greater than 2 (minimum size of a intersection)) by 
alphabetic order,using the function sort_ to first order the vector stop_lines.
and then printing the lines correctly ordered.
*/
void list_intersections()
{   
    int i,j;
    for ( i = 0; i < count_s; i++)
    {
        if(stops[i].num_lines >=2)
        {
            printf("%s %d:",stops[i].name,stops[i].num_lines);
            sort_(i);
            for(j = 0; j < stops[i].count_stop_l; j++)
                printf(" %s", stops[i].stop_lines[j]);
            printf("\n");
        }
        
    }
}


/*This function will read and call all the necessary things to be able to 
sucessfully make links between stops in a line */
void read_link()
{
    /*This control variable acts like a red/green sign, 0/1, respectively*/
    int i = 0, line_i, start_s_i = 0, destination_s_i = 0, control = 1;
    char temp[MAX_S_NAME];
    float price,duration;
    line l;

    getchar();/*ignores the first space*/
    strcpy(l.name,read_name('l'));
    getchar(); /*ignores the space after the name*/

    if(exists(l.name,count_l,'l') == -1)
        printf("%s: no such line.\n",l.name);
    else
    {   
        line_i = exists(l.name,count_l,'l');

        strcpy(l.start_s.name,read_name('s'));/*gets the line start stop name*/
        getchar(); /*ignores space*/
        /*if the start stop doesn't exist in the stops vector*/
        if(exists(l.start_s.name,count_s,'s') == -1)
            printf("%s: no such stop.\n",l.start_s.name);

        start_s_i = exists(l.start_s.name,count_s,'s');

        strcpy(l.destination_s.name, read_name('s'));
        
        if(exists(l.destination_s.name,count_s,'s') == -1)
            printf("%s: no such stop.\n",l.destination_s.name);

        destination_s_i = exists(l.destination_s.name,count_s,'s');

        if(scanf("%f %f",&price, &duration) == 2){
            if(price < 0 || duration < 0 ){
                printf("negative cost or duration.\n");
                control = 0;
            }
        }
        /*inicializar rt.dest.name e rt.origem.name com as primeiras duas paragens que nao existam no vetor rt.all_s */
        if(control == 1 && count_links < MAX_LINKS)
        {
            if(lines[line_i].count_line_s == 0)
            {  
                if(strcmp(l.start_s.name,l.destination_s.name) == 0)
                {   
                    control = 0;
                }
                else
                { 
                    strcpy(lines[line_i].all_line_s[FIRST],l.start_s.name);
                    strcpy(lines[line_i].all_line_s[SEC],l.destination_s.name);
                    lines[line_i].count_line_s++;
                    /*Adds two stops but the counter only increments by 1 because 0 is also an index to the all_s vector*/
                    lines[line_i].num_stops += 2;

                    stops[start_s_i].num_lines++;
                    strcpy(stops[start_s_i].stop_lines[stops[start_s_i].count_stop_l++],lines[line_i].name);
                    

                    stops[destination_s_i].num_lines++;
                    strcpy(stops[destination_s_i].stop_lines[stops[destination_s_i].count_stop_l++],lines[line_i].name);
                    
                }

            }
            else 
            {   /*1st case: circular lines*/
                if((strcmp(lines[line_i].all_line_s[FIRST],l.destination_s.name) == 0) &&
                strcmp(lines[line_i].all_line_s[lines[line_i].count_line_s],l.start_s.name) == 0 )
                {
                    lines[line_i].count_line_s++;
                    lines[line_i].num_stops++;
                    strcpy(lines[line_i].all_line_s[lines[line_i].count_line_s],l.destination_s.name);
                    /*adicionar a ligacao no final da carreira*/

                }
                /*2nd case: adds a stop in the beginning of the line*/
                else if(strcmp(lines[line_i].all_line_s[FIRST],l.destination_s.name) == 0)
                {   
                    strcpy(temp,lines[line_i].all_line_s[lines[line_i].count_line_s]);

                     for(i = lines[line_i].count_line_s; i >= 0; i--)
                        strcpy(lines[line_i].all_line_s[i+1],lines[line_i].all_line_s[i]);

                    strcpy(lines[line_i].all_line_s[FIRST],l.start_s.name);
                    lines[line_i].count_line_s++;
                    strcpy(lines[line_i].all_line_s[lines[line_i].count_line_s],temp);
                    lines[line_i].num_stops++;

                    stops[start_s_i].num_lines++;
                    strcpy(stops[start_s_i].stop_lines[stops[start_s_i].count_stop_l++],lines[line_i].name);
                    
                }
                /*3rd case: adds a new destination stop on the final of the line*/
                else if(strcmp(lines[line_i].all_line_s[lines[line_i].count_line_s],l.start_s.name) == 0)
                {
                    lines[line_i].count_line_s++;
                    strcpy(lines[line_i].all_line_s[lines[line_i].count_line_s],l.destination_s.name);
                    lines[line_i].num_stops++;
                    
                    stops[destination_s_i].num_lines++;
                    strcpy(stops[destination_s_i].stop_lines[stops[destination_s_i].count_stop_l++],
                    lines[line_i].name);
                    
                }
                /*4th case: impossible to link, so prints an error*/
                else
                {
                    printf("link cannot be associated with bus line.\n");
                    control = 0;
                    }
            }
            if(control == 1){
                lines[line_i].total_price += price;
                lines[line_i].total_duration += duration;
            }
            strcpy(lines[line_i].start_s.name,lines[line_i].all_line_s[FIRST]);
            strcpy(lines[line_i].destination_s.name,lines[line_i].all_line_s[lines[line_i].count_line_s]);
            lines[line_i].num_links++;
            count_links++;
            
        }
    }
}
   


/*
This is a funtion that reads a name from the stdin(standard input) 
and returns it.
Recieves a character from the input in order to know if it will read a 
line name or a stop name so the maximum size is not bigger than it shoud be.
*/
char * read_name(char character)
{   
    /*static varible in order to be able to return it later*/
    static char string[MAX_S_NAME]; 
    char c;
    int i = 0;
    /*state keeps track if it is reading inside quotation marks or not*/
    int state = OUT; 
    int size = MAX_S_NAME; /*Maximum size for the return string*/
    if(character == 'l')
        size = MAX_L_NAME;
    /* read the characters to form the string name while they are not equal
    to '\n' and the string is smaller than size */
    while   ((c = getchar()) != '\n' && i < size)
    {        
        if  (c == '\"')
        {   
            /*if quotation marks are found for the first time, state is in*/
            if(state == OUT) 
                state = IN;
            else
                state = OUT; /*state changes to out on the second time found*/
        }
        /*if the state is out, any space means that the name ends*/
        else  if(isspace(c) && state == OUT)
            break;
        else
            /*adds the character to the correspondent position of the string*/
            string[i++] = c; 
    }
    string[i] = '\0';/*delimits the string*/
    /*pushes the last read char back to the stdin so it can be used after*/
    ungetc(c,stdin);
    return string;
}

int is_inverso(char word[])
{
    int len_s = strlen(word);
    int len_inv = strlen("inverso");
    if(len_s >= 3 && len_s <= len_inv) /*Restringe a abreviatura de 3 a 7 letras*/
    {
        if(strncmp("inverso", word, len_s) == 0)/*Se a word for igual as n(len_s) primeiras letras de inverso,retorna true*/
            return TRUE;
    }
    return FALSE;
}


/*
This funtion will print all lines already created and some of their fields:
-If there are no stops linked to the line, it will print only the line name,
the number of stops, the total price and total duration, which are all 
initialized to 0 from another function.
-Else, it will print the line name, the start and destination stops names,
the number of stops and the total price and total duration.
*/
void list_lines()
{
    int i;
    for(i = 0; i < count_l; i++)
    {   

        if(lines[i].num_links == 0)
        {   
            printf("%s %d %.2f %.2f\n", lines[i].name,lines[i].num_stops,
            lines[i].total_price,lines[i].total_duration);
        }
        else
        { 
            printf("%s %s %s %d %.2f %.2f\n", lines[i].name,
            lines[i].all_line_s[0],lines[i].all_line_s[lines[i].count_line_s],lines[i].num_stops,
            lines[i].total_price,lines[i].total_duration);
        }
    }     
}


/*
This funtion will print all stops of a given line (from bottom to top or top
to bottom if it reads one of inverso abbreviations), if the line already 
exists, else, it will create a new line from the one on the input argument
*/
void add_line(line l,char word[])
{   
    int i;
    if(exists(l.name, count_l,'l') != -1)
    {
        int line_index = exists(l.name,count_l,'l');
        if(lines[line_index].num_links > 0)
        {   
            if(is_inverso(word))
            {
                for(i = lines[line_index].count_line_s ; i > 0; i--)   
                    printf("%s, ",lines[line_index].all_line_s[i]);
                printf("%s\n",lines[line_index].all_line_s[i]);
            }
            else
            {
                for(i = 0; i < lines[line_index].count_line_s; i++)   
                    printf("%s, ",lines[line_index].all_line_s[i]);
                printf("%s\n",lines[line_index].all_line_s[i]);
            }
        }  
    }
    
    else
    { /*A new line is created */
        if(count_l < MAX_LINES){

            strcpy(lines[count_l].name,l.name);
            lines[count_l].num_stops = 0;
            lines[count_l].total_price = 0.0;
            lines[count_l].total_duration = 0.0;
            lines[count_l].num_links = 0;
            lines[count_l].count_line_s = 0;
            count_l++;
        }

    }
}


/*
This is the main function of the command c that will use the function 
list_lines to print all previous created lines from lines vector if zero
arguments are given on the input. If there is one argument, the add_line
function is called. If there are two, the function will determine if the
word given is equal to inverso or it's abbreviations,if not, it will print
an error
*/
void read_line()
{   
    int i = 0;
    char c;
    /*Word read from the stdin and compared to inverso's abbreviations after*/
    char word[INVERSO_LENGTH]; 
    line l; /*local line variable to store the read values*/
    if((c = getchar()) == '\n')
    {
        list_lines();
    }
    else    
    {   
        strcpy(l.name, read_name('l')); 

        if((c = getchar()) == '\n')
            add_line(l,"\0");
        else
        {   i = 0;
            while(!isspace(c = getchar()))
                word[i++] = c;
            word[i] = '\0';

            if(is_inverso(word))
                add_line(l,word);
            else
                printf("incorrect sort option.\n");
        }
    }  
}


/*
This is the main function of the command p that will call all the necessary
functions to either print the fields of the stop
(if 0 arguments are given after the command), to print just the latitude and 
longitude of a given stop (1 arg) or to add a hole stop to the stops vector
(3 args)
*/
void add_list_stops()
{   char c;
    if((c = getchar()) == '\n')
        list_stops(); /*0 args*/
    else
    {   
        /*1 and 3 args*/
        stop_process();
    }

}

/*
This function will print every field except the stop_lines vector of each stop
 */
void list_stops()
{   
    int i;
    
    for(i = 0; i < count_s; i++)
    {
        printf("%s: %16.12f %16.12f %d\n", stops[i].name,stops[i].latitude,
        stops[i].longitude,stops[i].num_lines);
    }
}


/*
If the stop that is recieved as input already exists, this function will 
display an error saying so, else it will add a new stop to the stops vector,
inicialize all its values and increment the stop counter variable
*/
void add_stop(stop s)
{   if(exists(s.name,count_s,'s') != -1)
        printf("%s: stop already exists.\n",s.name);
    else{
        if(count_s < MAX_STOPS)
        {
            strcpy(stops[count_s].name,s.name);
            stops[count_s].latitude = s.latitude;
            stops[count_s].longitude = s.longitude;
            stops[count_s].num_lines = 0;
            stops[count_s].count_stop_l = 0;
            count_s++;
        }
    }
}


/*
This function will be used for the cases where at least one argument is given
after the command p.
Starts by reading the first argument, the stop name, using read_name function,
then, if there are no more arguments, it will print the latitude and longitude 
of the stop, else it will read the latitude and longitude and create a new stop
with the funtion add_stop using all the stored values
*/
void stop_process()
{   
    stop s;
    char c;
    /*reads the name and copies it to the local variable s name*/
    strcpy(s.name, read_name('s')); 
    
    /*1 argument*/
    if((c = getchar()) == '\n')
    {
        if(exists(s.name,count_s,'s') != -1)
        {   
            int stop_index = exists(s.name,count_s,'s');
            printf("%16.12f %16.12f\n",stops[stop_index].latitude,stops[stop_index].longitude);
        }
        else
            printf("%s: no such stop.\n",s.name);
    }
    /*no caso de receber 3 argumentos, adiciona uma stop com recurso a funcao add_stop(stop p)*/
    else{
        if(scanf("%lf %lf", &s.latitude, &s.longitude) == 2){
            add_stop(s);
        }
    }
}

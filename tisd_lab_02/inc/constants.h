#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_ADRESS 25

#define OK 0

typedef struct
{
    bool furnished; 
} primary;


typedef struct
{
    int year_of_construction;
    int count_of_owners;
    bool were_animals;
} secondary;


typedef union 
{
    primary primary_flat;
    secondary secondary_flat;    
} type_of_flat;


typedef struct
{
    char adress[MAX_ADRESS];
    int square;
    int rooms;
    int price_of_sq;
    type_of_flat flat_type;
} flat;


#endif
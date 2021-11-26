#include "../headers/item.h"
#include "../headers/craft.h"

const int craftCount = 25;

const craft craftList[25] = {

        { 1,1,{3,5},1,{1, 2, 3}
        },
        { 2,8,{{2,5},{3,6}},2,{1, 2, 3}
        },
        { 3,19,{{2,16},{4,17}},2,{0, 2, 3}
        },
        { 4,30,{{2,27},{2,28 }},2,{0, 0, 3}
        },
        { 5,9,{{3,5},{4,6}},2,{1, 2, 3}
        },
        { 6,20,{{3,16},{4,17}},2,{0, 2, 3}
        },
        { 7,31,{{2,27},{5,28}},2,{0, 0, 3}
        }, 
        { 8,10,{{2,5},{6,6}},2,{1, 2, 3}
        },
         {9,21,{{2,16},{7,17}},2,{0, 2, 3}
        },
         { 10,32,{{2,27},{8,28}},2,{0,0, 3}
        },
         { 11,11,{10,6},1,{1, 2, 3}
        },
         { 12,22,{12,17},1,{0, 2, 3}
        },
         { 13,33,{16,28},1,{0, 0, 3}
        },
         { 14,2,{3,5},1,{1, 2, 3}
        },
         { 15,12,{{2,5},{3,6}},2,{1, 2, 3}
        },
         { 16,23,{{2,16},{4,17}},2,{0, 2, 3}
        },
         { 17,4,{3,5},1,{1, 2, 3}
        },
         { 18,14,{{2,5},{3,6}},2,{1, 2, 3}
        },
         { 19,25,{{2,16},{4,17}},2,{0, 2, 3}
        },
         { 20,3,{3,5},1,{1, 2, 3}
        },
         { 21,13,{{2,5},{3,6}},2,{1, 2, 3}
        },
         { 22,24,{{2,5},{4,17}},2,{0, 2, 3}
        },
         { 23,15,{2,7},1,{1, 2, 3}
        },
         { 24,26,{2,18},1,{0, 2, 3}
        },
         { 25,34,{2,29},1,{0, 0, 3}
        },
      
}; 
const craft* getCraftsData() {
        return craftList;           
    }

const craft* getCraftDataByZone(int Zone) 
{
    int t=0;
    craft tabCraft[25];
    for (int i = 0; i < craftCount; ++i) 
    {
        for (int j = 0; j < 3  ; j++) 
        {
            if(craftList[i].avaliableZones[j] == Zone)
            {
                tabCraft[t]=craftList[i];
                t++;
            }
        
        }
   
    }
}
const craft getCraftDataByid(int id) {
    for (int i = 0; i < craftCount; ++i) {
        if(craftList[i].id == id){
            return craftList[i];
        }
    } 

}
    
void printCraftDataById(int id) {

    const craft data = getCraftDataByid(id);

    printf("\tId de l'craft : %d\n", data.id);
    printf("\ttargetItemId : %d\n", data.targetItemId);
    printf("\tingredient : %d\n", data.ingredient->id);
    printf("\tingredient : %d\n", data.ingredient->qty);
    printf("\tingNumber : %d\n", data.ingNumber);
    for ( int i=0;i<3;i++){
        printf("\tavaliableZones : %d\n", data.avaliableZones[i]);

    }     
}


item* craftItem ( item* items,int itemId){
return NULL;

}
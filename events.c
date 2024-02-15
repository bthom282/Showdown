/*******************************************************************************************
Names:    Adam Cole, Brooklyn Thomson

Purpose:  Implements event-handling functions for each of the specified asynchronous,
          synchronous and condition-based events.
*******************************************************************************************/
#include "events.h"

int checkCollision(BoundingBox box1, BoundingBox box2) {
    /* Calculate the sides of the first box */
    int left1 = box1.position.x;
    int right1 = box1.position.x + box1.size.width;
    int top1 = box1.position.y;
    int bottom1 = box1.position.y + box1.size.height;

    /* Calculate the sides of the second box*/
    int left2 = box2.position.x;
    int right2 = box2.position.x + box2.size.width;
    int top2 = box2.position.y;
    int bottom2 = box2.position.y + box2.size.height;

    /*Check for intersection*/ 
    if (bottom1 < top2 || top1 > bottom2 || right1 < left2 || left1 > right2) {
        /*No intersection*/ 
        return 0;
    } else {
        /*Intersection*/ 
        return 1;
    }
}

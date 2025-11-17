
// gcc -o ./house_dir/house graphics.c ./house_dir/house.c
//  ./house_dir/house | java -jar drawapp-4.5.jar

#include ".././graphics.h"

int main(void)
{
    drawRect(50,100,200,150);
    drawLine(50,100,150,25);
    drawLine(150,25,250,100);
    drawRect(130,190,40,60);
    drawRect(70,195,40,30);
    drawRect(190,195,40,30);
    drawRect(70,125,40,30);
    drawRect(190,125,40,30);
    return 0;
}
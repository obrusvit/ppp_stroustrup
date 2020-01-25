#include "std_lib_facilities.h"
#include "Simple_window.h"
#include "Window.h"
#include "Graph.h"

int main(){
    try {
        //
        using namespace Graph_lib; 
        cout << "Starting...\n";
        const int x_max = 1000;
    
        const int y_max = 800;
        const int grid_x_gap = 100;
        const int grid_y_gap = 100;

        const int grid_x_max = 800;
        const int grid_y_max = 800;
        
        Point tl {100, 100};
        Simple_window window{tl, x_max, y_max, "Drill 13"};
        Lines grid;
        for(int x = 0; x <= grid_x_max; x+=grid_x_gap){ 
            grid.add(Point{x, 0}, Point{x, grid_y_max});
        }
        for(int y = 0; y <= grid_y_max; y+=grid_y_gap){
            grid.add(Point{0, y}, Point{grid_x_max, y});
        }
        Image img{Point{0, 0}, "../some_imgs/morning_RPG_view.jpg", Suffix::jpg}; 
        img.set_mask(Point{0,0}, grid_x_gap, grid_y_gap);
        cout << img.point(0).x << "\n";
        
        
        window.attach(grid);
        window.attach(img);


        while(true){
            window.wait_for_button();
            img.move(grid_x_gap, 0);
            if(img.point(0).x >= grid_x_max){
                img.move(-grid_x_max, grid_y_gap);
            }
            if(img.point(0).y >= grid_y_max){
                img.move(0, -grid_y_max);
            }
            
            cout << img.point(0).x << "\n";
        }
        return 0;
    }
    catch(exception& e){
        cerr << e.what() << "\n";
        return 1;
    }
    catch(...){
        cerr << "something went wrong\n";
        return 2;
    }
}

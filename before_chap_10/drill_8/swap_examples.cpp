void swap_v(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}

void swap_r(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

int main(){
    int x = 7;
    int y = 9;
    swap_r(x,y);
    swap_v(7,9);

    const int cx = 7;
    const int cy = 9;
    swap_v(cx,cy);
    double dx = 7.7;
    double dy = 9.9;
    swap_v(dx,dy);

}

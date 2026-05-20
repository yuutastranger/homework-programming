#include <iostream>
#include <vector>
using namespace std;


struct point{
    int x, y;
};

point operator-(point a, point b){
    return {a.x - b.x, a.y - b.y};
}

int operator^(point a, point b){
    return a.x * b.y - a.y * b.x;
}

bool operator==(point a, point b){
    return a.x == b.x && a.y == b.y;
}

vector<point> jarvis(vector<point> points) {
    point p0 = points[0];
    for(point p : points){
        if(p.x < p0.x || (p.x == p0.x && p.y < p0.y)){
            p0 = p;
        }
    }
    point start = p0;
    vector<point> shell = {p0};
    while(true){
        point temp = points[0]; 
        for(point p : points){
            if(p == p0){
                continue;
            }
            if(temp == p0 || ((p - p0) ^ (temp - p0)) > 0){
                temp = p;
            }
        }
        if(temp == start){
            break;
        }
        p0 = temp;
        shell.push_back(temp);
    }
    return shell;
}
int main(){
    int n, x, y;
    vector<point> points;
    cout << "Enter amount of your points: "; cin >> n ;
    for(int i = 0; i < n; i++){
        cout << "x" << i << " = "; cin >> x;
        cout << "y" << i << " = "; cin >> y;
        points.push_back({x, y});
        cout << endl;
    }
    vector<point> result = jarvis(points);
    for(int i = 0; i < result.size(); i++){
        cout << result[i].x << " " << result[i].y << endl;
    }
    
    return 0;
}
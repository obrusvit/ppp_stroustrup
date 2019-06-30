#include "std_lib_facilities.h"

inline void prompt_seed(){
    cout << "enter seed: \n";
    int seed;
    cin >> seed;
    if(cin)
        seed_randint(seed);
    else
        error("wrong seed");
    
}

vector<int> get_vec_to_guess(){
    vector<int> ret;
    bool ret_ready = false;
    while (!ret_ready) {
      int to_add = randint(9);

      if (find(ret, to_add) == ret.end())
        ret.push_back(to_add);

      if (ret.size() == 4)
        ret_ready = true;
    }
    for( int r : ret){
        cout << r << " ";
    }
    cout << "\n";
    return ret;
}

bool prompt_playing(){
    cout << "Play again? (y/n)\n";
    char ans;
    cin >> ans;
    if(ans != 'y')
        return false;
    else 
        return true;
}

bool play_game(vector<int> to_guess){

    vector<int> guessed = {-1,-1,-1,-1};

    while(guessed != to_guess){
        cout << "Enter four numbers:\n";
        
        for(unsigned int i = 0; i < guessed.size(); ++i){
            int temp;
            cin >> temp;
            if(cin)
                guessed[i] = temp;
            else 
                error("only integers allowed");
        }

        int bulls = 0;
        int cows = 0;
        for(unsigned int i = 0; i < to_guess.size(); ++i){
            if(guessed[i] == to_guess[i]) 
                ++bulls;
            else if(find(guessed, to_guess[i]) != guessed.end()) 
                ++cows;
        }
        cout << bulls << " bulls, " << cows << " cows.\n";
    }
    cout << "You won!\n";
    return prompt_playing();

}

int main(){
    try{
        prompt_seed();
        bool playing = true;
        while(playing){
            vector<int> to_guess = get_vec_to_guess();
            playing = play_game(to_guess);
        }
        return 0;
    } catch(runtime_error& e){
        cerr << "runtime error: " << e.what() << "\n";
        return 1;
    }
}

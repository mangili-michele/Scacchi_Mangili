#include <iostream>
#include <string>
#include <cctype>
#include <windows.h>



using namespace std;

char board[8][8] = {
    {'r','n','b','q','k','b','n','r'},
    {'p','p','p','p','p','p','p','p'},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {'P','P','P','P','P','P','P','P'},
    {'R','N','B','Q','K','B','N','R'}
};

void stampaScacchiera() {
    cout << "\n";
    cout << "        a    b    c    d    e    f    g    h\n";
    cout << "      ╔════╦════╦════╦════╦════╦════╦════╦════╗\n";

    for(int i = 0; i < 8; i++) {
        cout << "    " << (8 - i) << " ║";
        for(int j = 0; j < 8; j++) {
            char piece = board[i][j];
            string symbol = " ";

            switch(piece) {
                case 'K': symbol = "♔"; break;
                case 'Q': symbol = "♕"; break;
                case 'R': symbol = "♖"; break;
                case 'B': symbol = "♗"; break;
                case 'N': symbol = "♘"; break;
                case 'P': symbol = "♙"; break;
                case 'k': symbol = "♚"; break;
                case 'q': symbol = "♛"; break;
                case 'r': symbol = "♜"; break;
                case 'b': symbol = "♝"; break;
                case 'n': symbol = "♞"; break;
                case 'p': symbol = "♟"; break;
                default: symbol = " ";
            }

            if(piece == ' ') {
                if((i + j) % 2 == 0)
                    cout << "    ";
                else
                    cout << " ▒▒ ";
            } else {
                cout << "  " << symbol << " ";
            }
            cout << "║";
        }
        cout << " " << (8 - i) << "\n";

        if(i < 7)
            cout << "      ╠════╬════╬════╬════╬════╬════╬════╬════╣\n";
    }

    cout << "      ╚════╩════╩════╩════╩════╩════╩════╩════╝\n";
    cout << "        a    b    c    d    e    f    g    h\n\n";
}

bool mossaValida(int sx, int sy, int dx, int dy) {
    if(sx < 0 || sx >= 8 || sy < 0 || sy >= 8 ||
       dx < 0 || dx >= 8 || dy < 0 || dy >= 8)
        return false;

    if(sx == dx && sy == dy) return false;

    char piece = board[sx][sy];
    if(piece == ' ') return false;

    char target = board[dx][dy];

    if(target != ' ') {
        bool bianco = isupper(piece);
        bool bersaglioBianco = isupper(target);
        if(bianco == bersaglioBianco) return false;
    }

    if(piece == 'P') {
        if(sx == 6 && dx == 4 && sy == dy &&
           board[5][dy] == ' ' && board[4][dy] == ' ')
            return true;
        if(dx == sx - 1 && sy == dy && board[dx][dy] == ' ')
            return true;
        if(dx == sx - 1 && abs(dy - sy) == 1 && islower(board[dx][dy]))
            return true;
    }

    if(piece == 'p') {
        if(sx == 1 && dx == 3 && sy == dy &&
           board[2][dy] == ' ' && board[3][dy] == ' ')
            return true;
        if(dx == sx + 1 && sy == dy && board[dx][dy] == ' ')
            return true;
        if(dx == sx + 1 && abs(dy - sy) == 1 && isupper(board[dx][dy]))
            return true;
    }

    if(piece == 'R' || piece == 'r') {
        if(sx == dx) {
            int step = (dy > sy) ? 1 : -1;
            for(int y = sy + step; y != dy; y += step)
                if(board[sx][y] != ' ') return false;
            return true;
        }
        if(sy == dy) {
            int step = (dx > sx) ? 1 : -1;
            for(int x = sx + step; x != dx; x += step)
                if(board[x][sy] != ' ') return false;
            return true;
        }
    }

    if(piece == 'N' || piece == 'n') {
        if((abs(dx - sx) == 2 && abs(dy - sy) == 1) ||
           (abs(dx - sx) == 1 && abs(dy - sy) == 2))
            return true;
    }

    if(piece == 'B' || piece == 'b') {
        if(abs(dx - sx) == abs(dy - sy)) {
            int stepX = (dx > sx) ? 1 : -1;
            int stepY = (dy > sy) ? 1 : -1;
            int x = sx + stepX;
            int y = sy + stepY;
            while(x != dx) {
                if(board[x][y] != ' ') return false;
                x += stepX;
                y += stepY;
            }
            return true;
        }
    }

    if(piece == 'Q' || piece == 'q') {
        return mossaValida(sx, sy, dx, dy); 
    }

    if(piece == 'K' || piece == 'k') {
        if(abs(dx - sx) <= 1 && abs(dy - sy) <= 1)
            return true;
    }

    return false;
}

bool muoviPezzo(int sx, int sy, int dx, int dy) {
    if(mossaValida(sx, sy, dx, dy)) {
        if(board[dx][dy] != ' ')
            cout << "Pezzo catturato!\n";

        board[dx][dy] = board[sx][sy];
        board[sx][sy] = ' ';
        return true;
    }

    cout << "Mossa non valida!\n";
    return false;
}

bool analizzaMossa(string mossa, int& sx, int& sy, int& dx, int& dy) {
    if(mossa.length() != 4) return false;

    char c1 = tolower(mossa[0]);
    char r1 = mossa[1];
    char c2 = tolower(mossa[2]);
    char r2 = mossa[3];

    if(c1 < 'a' || c1 > 'h' || c2 < 'a' || c2 > 'h') return false;
    if(r1 < '1' || r1 > '8' || r2 < '1' || r2 > '8') return false;

    sy = c1 - 'a';
    sx = 8 - (r1 - '0');
    dy = c2 - 'a';
    dx = 8 - (r2 - '0');

    return true;
}

int main() {
	SetConsoleOutputCP(CP_UTF8);
    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║      GIOCO DI SCACCHI IN C++       ║\n";
    cout << "╚════════════════════════════════════╝\n";

    stampaScacchiera();

    string mossa;
    int sx, sy, dx, dy;
    int turno = 0;

    while(true) {
        string giocatore = (turno % 2 == 0) ? "BIANCO" : "NERO";
        cout << "Turno " << (turno / 2 + 1) << " - Giocatore " << giocatore << "\n";
        cout << "Inserisci la mossa (es: e2e4 oppure 'quit'): ";
        cin >> mossa;

        if(mossa == "quit" || mossa == "q")
            break;

        if(analizzaMossa(mossa, sx, sy, dx, dy)) {
            if(muoviPezzo(sx, sy, dx, dy)) {
                stampaScacchiera();
                turno++;
            }
        } else {
            cout << "Formato non valido!\n\n";
        }
    }

    return 0;
}
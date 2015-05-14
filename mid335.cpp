//CMPS 335
//mid335.cpp
//Git repo name: mid335
//Coder: Kevin OBrien
//Style implimented: K&R
//
//Extra Credit: with tolerance = 0.005, how many bad values?
//Answer: 2

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

//frequency definitions
#define A4 440.0
#define F0 A4
#define F0_note A
#define F0_octave 4

typedef enum {
    Z = 0,
    C,
    Cs,
    D,
    Ds,
    E,
    F,
    Fs,
    G,
    Gs, 
    A,
    As,
    B,
    END = B,
    HALF_STEPS_PER_OCTAVE = B 
} note_t;

double freq(note_t note, int octave_delta);
void unitTest(note_t note, int octave_delta);

double results[13][9] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
    16.35, 32.70, 65.41, 130.81, 261.63, 523.25, 1046.50, 
    2093.00, 4186.01,
    17.32, 34.65, 69.30, 138.59, 277.18, 554.37, 1108.73, 
    2217.46, 4434.92,
    18.35, 36.71, 73.42, 146.83, 293.66, 587.33, 1174.66, 
    2349.32, 4698.63,
    19.45, 38.89, 77.78, 155.56, 311.13, 622.25, 1244.51, 
    2489.02, 4978.03,
    20.60, 41.20, 82.41, 164.81, 329.63, 659.25, 1318.51, 
    2637.02, 5274.04,
    21.83, 43.65, 87.31, 174.61, 349.23, 698.46, 1396.91, 
    2793.83, 5587.65,
    23.12, 46.25, 92.50, 185.00, 369.99, 739.99, 1479.98,
    2959.96, 5919.91,
    24.50, 49.00, 98.00, 196.00, 392.00, 783.99, 1567.98,
    3135.96, 6271.93,
    25.96, 51.91, 103.83, 207.65, 415.30, 830.61, 1661.22,
    3322.44, 6644.88,
    27.50, 55.00, 110.00, 220.00, 440.00, 880.00, 1760.00,
    3520.00, 7040.00,
    29.14, 58.27, 116.54, 233.08, 466.16, 932.33, 1864.66,
    3729.31, 7458.62,
    30.87, 61.74, 123.47, 246.94, 493.88, 987.77, 1975.53,
    3951.07, 7902.13};


double ret;
double tolerance;
double diff;
int count = 0;

int main (int argc, char * argv[]) {

    note_t note;
    int octave_delta;

    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <NOTE>  <OCTAVE_DELTA> <TOLERANCE>" << endl;
        return 0;
    }

    octave_delta = atoi(argv[2]);
    tolerance = atof(argv[3]);

    cout << "note\t\toctave\t\tvalue\t\tdiff\n";
    cout << "----\t\t------\t\t-----\t\t----\n";


    note = (note_t)(toupper(argv[1][0]));

    switch (toupper(argv[1][0])) {
        case 'Z': note = C; break;
        case 'A': note = A; break;
        case 'B': note = B; break;
        case 'C': note = C; break;
        case 'D': note = D; break;
        case 'E': note = E; break;
        case 'F': note = F; break;
    }
    //You may call your unit test here...

    unitTest(note, octave_delta);

    return 0;
}

//-----------------------------------------------------------
//Generate a frequency in hz that is half_steps away from C_4
//Do not modify this function.
//-----------------------------------------------------------
double freq(note_t note, int octave_delta)
{
    double freq;
    double factor;
    double a;
    int n;
    int octave = octave_delta - F0_octave;

    a = pow(2.0, 1.0/(double)HALF_STEPS_PER_OCTAVE);
    n = note - F0_note;
    freq = F0 * pow(a, (double)n);
    factor = pow(2.0, (double)octave);
    freq = freq * factor;
    return freq;
}

void unitTest(note_t note, int octave_delta){

    while (octave_delta < 9) {

        ret = freq(note, octave_delta);
        diff = ret - results[note][octave_delta];
        diff = abs(diff);

        cout << note << "\t\t" << octave_delta << "\t\t"
            << ret << "\t\t" <<  diff;

        if (diff <= tolerance) {
            if (diff == 0)
                cout << "\t";

            cout << "\t\tgood\n";
        } else {

            cout << "\t<-------BAD\n";
            count++;
        }

        if (note == B) {

            octave_delta++;
        }

        switch (note) {
            case Z  : note = C;  break;
            case C  : note = Cs; break;
            case Cs : note = D;  break;
            case D  : note = Ds; break;
            case Ds : note = E;  break;
            case E  : note = F;  break;
            case F  : note = Fs; break;
            case Fs : note = G;  break;
            case G  : note = Gs; break;
            case Gs : note = A;  break;
            case A  : note = As; break;
            case As : note = B;  break;
            case B  : note = C;  break;
        }
    }

    cout << "bad values: " << count << endl;
}

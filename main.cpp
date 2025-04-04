#include "matrix.hpp"
#include <fstream>
#include <stdexcept>
using namespace std;

// read matrix from file
Matrix readMatrixFile(const string& filename, bool firstMatrix = true) {
    ifstream file(filename);
    // error if unable to open file
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open file.");
    }
    size_t N;
    file >> N;
    vector<vector<int>> matrixData(N, vector<int>(N));
    if (firstMatrix) {
        // read first matrix
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (!(file >> matrixData[i][j])) {
                    throw runtime_error("Error: File data is invalid.");
                }
            }
        }
    } else {
        // skip first 
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                int temp;
                if (!(file >> temp)) {
                    throw runtime_error("Error: File data is invalid.");
                }
            }
        }
        // read second
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (!(file >> matrixData[i][j])) {
                    throw runtime_error("Error: File data is invalid.");
                }
            }
        }
    }
    file.close();
    return Matrix(matrixData);
}
string userFile(int argc, char* argv[]) {
    if (argc == 2) {
        return argv[1];
    } else {
        // get user's file
        string filename;
        while (true) {
            cout << "Enter matrix file name: ";
            cin >> filename;
            // check if file exists
            ifstream testFile(filename);
            if (testFile.good()) {
                testFile.close();
                return filename;
            // error handling
            } else {
                cout << "Error: Unable to open file.\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
    }
}

//main function
int main(int argc, char *argv[]) {
    try {
        // get file from user
        string filename = userFile(argc, argv);
        // read file
        Matrix m1 = readMatrixFile(argv[1], true);
        Matrix m2 = readMatrixFile(argv[1], false);
        // print matrices as-is
        cout << "Matrix 1: " << endl;
        m1.print_matrix();
        cout << "\nMatrix 2: " << endl;
        m2.print_matrix();
        // add matrices together & print result
        cout << "\nMatrix 1 + 2: " << endl;
        Matrix sum = m1 + m2;
        sum.print_matrix();
        // multiply matrices & print result
        cout << "\nMatrix 1 * Matrix 2: " << endl;
        Matrix product = m1 * m2;
        product.print_matrix();
        // find diagonal sums; main & secondary
        cout << "\n Main diagonal sum: " << m1.sum_diagonal_major() << endl;
        cout << "\nSecondary diagonal: " << m1.sum_diagonal_minor() << endl;
        // swap rows 
        cout << "\nSwap rows 0 and 1: " << endl;
        Matrix swapRows = m1;
        swapRows.swap_rows(0, 1);
        swapRows.print_matrix();
        // swap columns
        cout << "\nSwap columns 0 and 1: " << endl;
        Matrix swapCols = m1;
        swapCols.swap_cols(0, 1);
        swapCols.print_matrix();
        // update elements
        Matrix update = m1;
        while (true) {
            try {
                size_t row, col;
                int newValue;
                // get row
                cout << "Enter row index (0-" << update.get_size()-1 << "): ";
                if (!(cin >> row)) {
                    throw runtime_error("Error: Input invalid.");
                }
                // get column
                cout << "Enter column index (0-" << update.get_size()-1 << "): ";
                if (!(cin >> col)) {
                    throw runtime_error("Error: Input invalid.");
                }
                // get new value
                cout << "Enter new value: ";
                if (!(cin >> newValue)) {
                    throw runtime_error("Error: Input invalid.");
                }
                update.set_value(row, col, newValue);
                break;
            // error handling
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        // print updated matrix
        cout << "\nUpdated Matrix: " << endl;
        update.print_matrix();
    // error handling
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}

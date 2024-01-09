#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <memory>
#include <stack>
#include <string>

using namespace std;

int b[1000001];
vector <int> c;

void bubbleSort(vector <int>& arr, int n)
{
    bool flag;
    for (int i = 0; i < n - 1; i++) {
        flag = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                flag = true;
            }
        }
        // nếu không có 2 phần tử nào được swap thì break
        if (flag == false)
            break;
    }
}
void quickSort(vector <int>& arr, int low, int high) {
    if (low < high) {
        int key = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < key) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1; //vị trí của pivot
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void insertionSort(vector <int>& a, int n)
{
    int j;
    for (int i = 1; i < n; i++) {
        j = i;
        while (j >= 1 && a[j-1] > a[j]) {
            swap(a[j], a[j - 1]); //swap đến khi i+1 phần tử đầu tiên được sort
            j = j - 1;
        }
    }
}
void sortByChoice(vector <int>& a)
{
    int choice;
    do {
        cout << "1. Bubble Sort" << endl;
        cout << "2. Quick Sort" << endl;
        cout << "3. Insertion Sort" << endl;
        cout << "Your choice: ";
        cin >> choice;
        clock_t begin;
        clock_t end;

        begin = clock();

        if (choice == 1) {
            bubbleSort(a, a.size() - 1);
            cout << "Sorted successfully" << endl;
        }
        if (choice == 2) {
            quickSort(a, 0, a.size() - 1);
            cout << "Sorted successfully" << endl;
        }
        if (choice == 3) {
            insertionSort(a, a.size() - 1);
            cout << "Sorted successfully" << endl;
        }

        end = clock();

        cout << "Time run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
    } while (choice != 1 && choice != 2 && choice != 3);
}
void reset(vector <int>& a, int n) //sau khi sort, mang can phai duoc rollback lai trang thai chua sort
{
    a.clear();
    for (int i = 0; i < n; i++) a.push_back(b[i]);
}
vector<int> importData(const string& filePath) //đẩy file vao vector
{
    ifstream file(filePath);
    vector<int> data;

    int number;

    while (file >> number)
    {
        data.push_back(number);
    }
    file.close();
    return data;
}
void generateData(int b[], int n) // tạo một mảng ngẫu nhiên có độ dài n
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        int r;
        r = rand();
        b[i] = r;
    }
}
void compare(int n) //In ra kết quả của 3 loại sort cho 1 mảng ngẫu nhiên gồm n phần tử
{
    cout << "Computing time run on " << n << " numbers: " << endl;
    generateData(b, n);

    clock_t begin;
    clock_t end;

    reset(c, n);
    begin = clock();
    bubbleSort(c, n);
    end = clock();
    cout << "Time for Bubble Sort run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;

    reset(c, n); //sau khi sort, mảng cần phải được rollback lại trạng thái ban đầu
    begin = clock();
    insertionSort(c, n);
    end = clock();
    cout << "Time for Insertion Sort run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;

    reset(c, n); //sau khi sort, mang can phai duoc rollback lai trang thai chua sort
    begin = clock();
    quickSort(c, 0, n - 1);
    end = clock();
    cout << "Time for Quick Sort run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
}
int main()
{
    string fileName;
    vector<int> data;
    int option;
    do {
        cout << "MENU" << endl;
        cout << "1. Import file" << endl;
        cout << "2. Sort" << endl;
        cout << "3. Save file" << endl;
        cout << "4. Test" << endl;
        cout << "5. Exit" << endl;
        cout << "Your option: ";
        cin >> option;
        if (option == 1) {
            cin.ignore();
            cout<<"Input your file name : ";
            getline(cin,fileName);
            vector<int> temp = importData(fileName);
            if (temp.size() <= 10000)
            {
                cout << "Please import a file having greater than 10000 numbers" << endl;
                temp.clear();
            }
            else
            {
                data = importData(fileName);
                cout << "File imported" << endl;
            }
        }
        if (option == 2) {
            sortByChoice(data);
        }
        if (option == 3) {
            string name;
            cin.ignore();
            cout << "Write your file name: ";
            getline(cin,name);
            ofstream file(name + ".txt");
            if (file.is_open())
            {
                for (int x : data) file << x << ' ';
            }
            file.close();
            cout << "Saved sucessfully" << endl;
        }
        if (option == 4){
            compare(10000);
            compare(100000);
            compare(1000000);
        }
    } while (option != 5);
}

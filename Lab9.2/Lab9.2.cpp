// Lab9.2.cpp
// Михайлов Олександр
// Впорядкування та бінарний пошук в масиві структур
// Варіант 24

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string>

using namespace std;

enum Speciality { KN, In, ME, FI, TN };

string specialityStr[]{ "КН","ІН","МЕ","ФІ","ТН" };

struct StudentA {
    string surname;
    int kurs;
    Speciality speciality;
    double physicsMark;
    double mathsMark;
    double OITmark;
};

struct StudentB {
    string surname;
    int kurs;
    Speciality speciality;
    double physicsMark;
    double mathsMark;
    union {
        double programmingMark;
        double chislMethodMark;
        double pedMark;
    };
};

void CreateA(StudentA* sa, const int amount) {
    int speciality;
    for (int i = 0; i < amount; i++) {
        cout << "Студент № " << i + 1 << ": " << endl;

        cin.get();
        cin.sync();

        cout << "   Прізвище: "; getline(cin, sa[i].surname);

        do {
            cout << "   Курс: "; cin >> sa[i].kurs;
            if (sa[i].kurs < 1 || sa[i].kurs > 6)
                cout << "   Є тільки 1-6 курси!" << endl;
        } while (sa[i].kurs < 1 || sa[i].kurs > 6);

        do {
            cout << "   Спеціальність (0 — КН, 1 — ІН, 2 — МЕ, 3 — ФІ, 4 — ТН): ";
            cin >> speciality;
            sa[i].speciality = (Speciality)speciality;

            if (speciality < 0 || speciality > 4)
                cout << "Ви ввели невірний номер!" << endl;
        } while (speciality < 0 || speciality > 4);

        do {
            cout << "   Оцінка з фізики: "; cin >> sa[i].physicsMark;
            if (sa[i].physicsMark <= 0 || sa[i].physicsMark > 5)
                cout << "Невірна оцінка!" << endl;
        } while (sa[i].physicsMark <= 0 || sa[i].physicsMark > 5);

        do {
            cout << "   Оцінка з математики: "; cin >> sa[i].mathsMark;
            if (sa[i].mathsMark <= 0 || sa[i].mathsMark > 5)
                cout << "Невірна оцінка!" << endl;
        } while (sa[i].mathsMark <= 0 || sa[i].mathsMark > 5);

        do {
            cout << "   Оцінка з інформатики: "; cin >> sa[i].OITmark;
            if (sa[i].OITmark <= 0 || sa[i].OITmark > 5)
                cout << "Невірна оцінка!" << endl;
        } while (sa[i].OITmark <= 0 || sa[i].OITmark > 5);

        cout << endl;
    }
}

void PrintA(StudentA* sa, const int amount) {
    cout << "===========================================================================" << endl;
    cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Інформатика |" << endl;
    cout << "---------------------------------------------------------------------------" << endl;

    for (int i = 0; i < amount; i++) {
        cout << "| " << right << i + 1 << " ";
        cout << "| " << setw(8) << left << sa[i].surname
            << " | " << setw(4) << left << sa[i].kurs
            << " | " << setw(13) << left << specialityStr[sa[i].speciality]
            << " | " << setw(6) << left << sa[i].physicsMark
            << " | " << setw(10) << left << sa[i].mathsMark
            << " | " << setw(11) << left << sa[i].OITmark
            << " |";
        cout << endl;
    }
    cout << "===========================================================================" << endl << endl;
}

double AverageMarkA(StudentA* sa, int index) {
    double AverageMark = (sa[index].physicsMark + sa[index].mathsMark + sa[index].OITmark) / 3.0;
    return AverageMark;
}

void SortA(StudentA* sa, const int amount) {
    StudentA tmp;
    
    for (int i0 = 0; i0 < amount - 1; i0++)
        for (int i1 = 0; i1 < amount - i0 - 1; i1++)
            if ((sa[i1].kurs > sa[i1 + 1].kurs) || (sa[i1].kurs == sa[i1 + 1].kurs && AverageMarkA(sa, i1) < AverageMarkA(sa, i1 + 1)) || (sa[i1].kurs == sa[i1 + 1].kurs && AverageMarkA(sa, i1) == AverageMarkA(sa, i1 + 1) && sa[i1].surname > sa[i1 + 1].surname)) {
                tmp = sa[i1];
                sa[i1] = sa[i1 + 1];
                sa[i1 + 1] = tmp;
            }
}

int* IndexSortA(StudentA* sa, const int amount) {
    int* IA = new int[amount];

    for (int i = 0; i < amount; i++)
        IA[i] = i;

    int i, j, value;
    for (i = 1; i < amount; i++) {
        value = IA[i];
        for (j = i - 1; (sa[IA[j]].kurs > sa[value].kurs) || (sa[IA[j]].kurs == sa[value].kurs && AverageMarkA(sa, IA[j]) < AverageMarkA(sa, value)) || (sa[IA[j]].kurs == sa[value].kurs && AverageMarkA(sa, IA[j]) == AverageMarkA(sa, value) && sa[IA[j]].surname > sa[value].surname); j--) {
            IA[j + 1] = IA[j];
        }
        IA[j + 1] = value;
    }
    return IA;
}

void PrintIndexSortedA(StudentA* sa, int* IA, const int amount) {
    cout << "===========================================================================" << endl;
    cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Інформатика |" << endl;
    cout << "---------------------------------------------------------------------------" << endl;

    for (int i = 0; i < amount; i++) { 
        cout << "| " << right << i + 1 << " ";
        cout << "| " << setw(8) << left << sa[IA[i]].surname
            << " | " << setw(4) << left << sa[IA[i]].kurs
            << " | " << setw(13) << left << specialityStr[sa[IA[i]].speciality]
            << " | " << setw(6) << left << sa[IA[i]].physicsMark
            << " | " << setw(10) << left << sa[IA[i]].mathsMark
            << " | " << setw(11) << left << sa[IA[i]].OITmark
            << " |";
        cout << endl;
    }
    cout << "===========================================================================" << endl << endl;
}

void BinSearchA(StudentA* sa, const int amount, int& answerA) {
    int kurs;
    double average;
    string surname;

    cout << "Введіть ключі пошуку:" << endl;
    cout << "   Введіть прізвище: "; cin >> surname;

    do {
        cout << "   Введіть курс: "; cin >> kurs;
        if (kurs < 1 || kurs > 6)
            cout << "   Є тільки 1-6 курси!" << endl;
    } while (kurs < 1 || kurs > 6);

    do {
        cout << "   Введіть середній бал: "; cin >> average;
        if (average < 1 || average > 5) {
            cout << "   Середній бал може бути від 1 до 5!" << endl;
        }
    } while (average < 1 || average > 5);

    for (int i = 0; i < amount; i++) {
        if (sa[i].kurs == kurs && sa[i].surname == surname && AverageMarkA(sa, i) == average) {
            answerA = 1;
        }
    }
}

void CreateB(StudentB* sb, const int amount) {
    int speciality;

    for (int i = 0; i < amount; i++) {
        cout << "Студент № " << i + 1 << ": " << endl;

        cin.get();
        cin.sync();

        cout << "   Прізвище: "; getline(cin, sb[i].surname);

        do {
            cout << "   Курс: "; cin >> sb[i].kurs;
            if (sb[i].kurs < 1 || sb[i].kurs > 6)
                cout << "   Є тільки 1-6 курси!" << endl;
        } while (sb[i].kurs < 1 || sb[i].kurs > 6);

        do {
            cout << "   Спеціальність (0 — КН, 1 — ІН, 2 — МЕ, 3 — ФІ, 4 — ТН): ";
            cin >> speciality;
            sb[i].speciality = (Speciality)speciality;

            if (speciality < 0 || speciality > 4)
                cout << "Ви ввели невірний номер!" << endl;
        } while (speciality < 0 || speciality > 4);

        do {
            cout << "   Оцінка з фізики: "; cin >> sb[i].physicsMark;
            if (sb[i].physicsMark <= 0 || sb[i].physicsMark > 5)
                cout << "Невірна оцінка!" << endl;
        } while (sb[i].physicsMark <= 0 || sb[i].physicsMark > 5);

        do {
            cout << "   Оцінка з математики: "; cin >> sb[i].mathsMark;
            if (sb[i].mathsMark <= 0 || sb[i].mathsMark > 5)
                cout << "Невірна оцінка!" << endl;
        } while (sb[i].mathsMark <= 0 || sb[i].mathsMark > 5);

        switch (sb[i].speciality) {
        case KN:
            do {
                cout << "   Оцінка з програмування: "; cin >> sb[i].programmingMark;
                if (sb[i].programmingMark <= 0 || sb[i].programmingMark > 5)
                    cout << "Невірна оцінка!" << endl;
            } while (sb[i].programmingMark <= 0 || sb[i].programmingMark > 5);
            break;
        case In:
            do {
                cout << "   Оцінка з чисельних методів: "; cin >> sb[i].chislMethodMark;
                if (sb[i].chislMethodMark <= 0 || sb[i].chislMethodMark > 5)
                    cout << "Невірна оцінка!" << endl;
            } while (sb[i].chislMethodMark <= 0 || sb[i].chislMethodMark > 5);
            break;
        case ME:
        case FI:
        case TN:
            do {
                cout << "   Оцінка з педагогіки: "; cin >> sb[i].pedMark;
                if (sb[i].pedMark <= 0 || sb[i].pedMark > 5)
                    cout << "Невірна оцінка!" << endl;
            } while (sb[i].pedMark <= 0 || sb[i].pedMark > 5);
            break;
        }
        cout << endl;
    }
}

void PrintB(StudentB* sb, const int amount) {
    cout << "============================================================================================================" << endl;
    cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні Методи | Педігогіка |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < amount; i++) {
        cout << "| " << right << i + 1 << " ";
        cout << "| " << setw(8) << left << sb[i].surname
            << " | " << setw(4) << left << sb[i].kurs
            << " | " << setw(13) << left << specialityStr[sb[i].speciality]
            << " | " << setw(6) << left << sb[i].physicsMark
            << " | " << setw(10) << left << sb[i].mathsMark;

        switch (sb[i].speciality) {
        case KN:
            cout << " | " << setw(13) << left << sb[i].programmingMark
                << " | " << setw(15) << left << "—" << " | " << setw(10) << left << "—" << " |";
            break;
        case In:
            cout << " | " << setw(13) << left << "—"
                << " | " << setw(15) << sb[i].chislMethodMark
                << " | " << setw(10) << left << "—" << " |";
            break;
        case ME:
        case FI:
        case TN:
            cout << " | " << setw(13) << left << "—"
                << " | " << setw(15) << left << "—"
                << " | " << setw(10) << left << sb[i].pedMark << " |";
        }
        cout << endl;
    }
    cout << "============================================================================================================" << endl << endl;
}

double AverageMarkB(StudentB* sb, int index) {
    double averageMark = 0;
    switch (sb[index].speciality) {
    case KN:
        averageMark = (sb[index].physicsMark + sb[index].mathsMark + sb[index].programmingMark) / 3.0;
        break;
    case In:
        averageMark = (sb[index].physicsMark + sb[index].mathsMark + sb[index].chislMethodMark) / 3.0;
        break;
    case ME:
    case FI:
    case TN:
        averageMark = (sb[index].physicsMark + sb[index].mathsMark + sb[index].pedMark) / 3.0;
        break;
    }
    return averageMark;
}

void SortB(StudentB* sb, const int amount) {
    StudentB tmp;

    for (int i0 = 0; i0 < amount - 1; i0++)
        for (int i1 = 0; i1 < amount - i0 - 1; i1++)
            if ((sb[i1].kurs > sb[i1 + 1].kurs) || (sb[i1].kurs == sb[i1 + 1].kurs && AverageMarkB(sb, i1) < AverageMarkB(sb, i1 + 1)) || (sb[i1].kurs == sb[i1 + 1].kurs && AverageMarkB(sb, i1) == AverageMarkB(sb, i1 + 1) && sb[i1].surname > sb[i1 + 1].surname)) {
                tmp = sb[i1];
                sb[i1] = sb[i1 + 1];
                sb[i1 + 1] = tmp;
            }
}

int* IndexSortB(StudentB* sb, const int amount) {
    int* IB = new int[amount];

    for (int i = 0; i < amount; i++)
        IB[i] = i;

    int i, j, value;
    for (i = 1; i < amount; i++) {
        value = IB[i];
        for (j = i - 1; (sb[IB[j]].kurs > sb[value].kurs) || (sb[IB[j]].kurs == sb[value].kurs && AverageMarkB(sb, IB[j]) < AverageMarkB(sb, value)) || (sb[IB[j]].kurs == sb[value].kurs && AverageMarkB(sb, IB[j]) == AverageMarkB(sb, value) && sb[IB[j]].surname > sb[value].surname); j--) {
            IB[j + 1] = IB[j];
        }
        IB[j + 1] = value;
    }
    return IB;
}

void PrintIndexSortedB(StudentB* sb, int* IB, const int amount) { 
    cout << "============================================================================================================" << endl;
    cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні Методи | Педігогіка |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < amount; i++) {
        cout << "| " << right << i + 1 << " ";
        cout << "| " << setw(8) << left << sb[IB[i]].surname
            << " | " << setw(4) << left << sb[IB[i]].kurs
            << " | " << setw(13) << left << specialityStr[sb[IB[i]].speciality]
            << " | " << setw(6) << left << sb[IB[i]].physicsMark
            << " | " << setw(10) << left << sb[IB[i]].mathsMark;

        switch (sb[IB[i]].speciality) {
        case KN:
            cout << " | " << setw(13) << left << sb[IB[i]].programmingMark
                << " | " << setw(15) << left << "—" << " | " << setw(10) << left << "—" << " |";
            break;
        case In:
            cout << " | " << setw(13) << left << "—"
                << " | " << setw(15) << sb[IB[i]].chislMethodMark
                << " | " << setw(10) << left << "—" << " |";
            break;
        case ME:
        case FI:
        case TN:
            cout << " | " << setw(13) << left << "—"
                << " | " << setw(15) << left << "—"
                << " | " << setw(10) << left << sb[IB[i]].pedMark << " |";
        }
        cout << endl;
    }
    cout << "============================================================================================================" << endl << endl;
}

void BinSearchB(StudentB* sb, const int amount,int &answerB) {
    int kurs;
    double average;
    string surname;

    cout << "Введіть ключі пошуку:" << endl;
    cout << "   Введіть прізвище: "; cin >> surname;

    do {
        cout << "   Введіть курс: "; cin >> kurs;
        if (kurs < 1 || kurs > 6)
            cout << "   Є тільки 1-6 курси!" << endl;
    } while (kurs < 1 || kurs > 6);

    do {
        cout << "   Введіть середній бал: "; cin >> average;
        if (average < 1 || average > 5) {
            cout << "   Середній бал може бути від 1 до 5!" << endl;
        }
    } while (average < 1 || average > 5);

    for (int i = 0; i < amount; i++) {
        if (sb[i].kurs == kurs && sb[i].surname == surname && AverageMarkB(sb, i) == average) {
            answerB = 1;
        }
    }
}

void TableA(StudentA* sa, const int amount) {
    int menu = 0;
    int answerA = 0;

    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl;
        cout << " [1] - вивести таблицю А" << endl;
        cout << " [2] - фізично впорядкувати таблицю А, вивести її на екран" << endl;
        cout << " [3] - індексно впорядкувати таблицю А, вивести її на екран" << endl;
        cout << " [4] - знайти чи є студент з вказаним прізвищем,курсом та середнім балом" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menu;
        cout << endl << endl;

        switch (menu) {
        case 0:
            break;
        case 1:
            PrintA(sa, amount);
            break;
        case 2:
            SortA(sa, amount);
            PrintA(sa, amount);
            break;
        case 3:
            PrintIndexSortedA(sa, IndexSortA(sa, amount), amount);
            break;
        case 4:
            BinSearchA(sa, amount, answerA);
            if (answerA == 1) {
                cout << endl << "   Такий студент існує!" << endl;
            }
            else {
                cout << endl << "   Такого студента не існує!" << endl;
            }
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню!" << endl;
            break;
        }

    } while (menu != 0);
}

void TableB(StudentB* sb, const int amount) {
    int menu = 0;
    int answerB = 0;
    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl;
        cout << " [1] - вивести таблицю В" << endl;
        cout << " [2] - фізично впорядкувати таблицю В, вивести її на екран" << endl;
        cout << " [3] - індексно впорядкувати таблицю В, вивести її на екран" << endl;
        cout << " [4] - знайти чи є студент з вказаним прізвищем,курсом та середнім балом" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menu;
        cout << endl << endl;

        switch (menu) {
        case 0:
            break;
        case 1:
            PrintB(sb, amount);
            break;
        case 2:
            SortB(sb, amount);
            PrintB(sb, amount);
            break;
        case 3:
            PrintIndexSortedB(sb, IndexSortB(sb, amount), amount);
            break;
        case 4:
            BinSearchB(sb, amount, answerB);
            if (answerB == 1) {
                cout << endl << "   Такий студент існує!" << endl;
            }
            else {
                cout << endl << "   Такого студента не існує!" << endl;
            }
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню!" << endl;
            break;
        }
    } while (menu != 0);
}

void BinSearchA_B(StudentA* sa, StudentB* sb, const int amount, int& answerA, int& answerB) {
    int kurs;
    double average;
    string surname;

    cout << "Введіть ключі пошуку:" << endl;
    cout << "   Введіть прізвище: "; cin >> surname;

    do {
        cout << "   Введіть курс: "; cin >> kurs;
        if (kurs < 1 || kurs > 6)
            cout << "   Є тільки 1-6 курси!" << endl;
    } while (kurs < 1 || kurs > 6);

    do {
        cout << "   Введіть середній бал: "; cin >> average;
        if (average < 1 || average > 5) {
            cout << "   Середній бал може бути від 1 до 5!" << endl;
        }
    } while (average < 1 || average > 5);

    for (int i = 0; i < amount; i++) {
        if (sb[i].surname == surname) {
            if (sb[i].kurs == kurs && sb[i].surname == surname && AverageMarkB(sb, i) == average) {
                answerB = 1;
            }
        }
        else if (sa[i].surname == surname) {
            if (sa[i].kurs == kurs && sa[i].surname == surname && AverageMarkA(sa, i) == average) {
                answerA = 1;
            }
        }
    }
}

void TableA_B(StudentA* sa, StudentB* sb, const int amount) {
    int kurs, answerA = 0, answerB = 0, menu = 0;
    double average;
    string surname;

    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl;
        cout << " [1] - вивести таблицю А та В" << endl;
        cout << " [2] - фізично впорядкувати таблиці А та В, вивести їх на екран" << endl;
        cout << " [3] - індексно впорядкувати таблиці А та В, вивести їх на екран" << endl;
        cout << " [4] - знайти чи є студент з вказаним прізвищем,курсом та середнім балом" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menu;
        cout << endl << endl;

        switch (menu) {
        case 0:
            break;
        case 1:
            PrintA(sa, amount);
            PrintB(sb, amount);
            break;
        case 2:
            SortA(sa, amount);
            SortB(sb, amount);
            PrintA(sa, amount);
            PrintB(sb, amount);
            break;
        case 3:
            PrintIndexSortedA(sa, IndexSortA(sa, amount), amount);
            PrintIndexSortedB(sb, IndexSortB(sb, amount), amount);
            break;
        case 4:
            BinSearchA_B(sa, sb, amount, answerA, answerB);
            if ((answerA == 1 && answerB == 1) || (answerA == 1 && answerB == 0) || (answerA == 0 && answerB == 1)) {
                cout << endl << "   Такий студент існує!" << endl;
            }
            else {
                cout << endl << "   Такого студента не існує!" << endl;
            }
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню!" << endl;
            break;
        }
    } while (menu != 0);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int amount, tableMenu = 0;

    do {
        cout << "Введіть кількість студентів в кожній таблиці: "; cin >> amount;
        if (amount < 1)
            cout << endl << "Кількість студентів не може бути меньше одного!" << endl << endl;
    } while (amount < 1);

    StudentA* sa = new StudentA[amount];
    StudentB* sb = new StudentB[amount];

    cout << endl << "Спочатку потрібно заповнити таблицю." << endl << "Якщо ви заповните тільки одну таблицю, працювати з іншою буде не можливо!" << endl;

    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl;
        cout << " [1] - ввести дані таблиці А" << endl;
        cout << " [2] - ввести дані таблиці В" << endl;
        cout << " [3] - ввести дані таблиці А та В" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> tableMenu;
        switch (tableMenu) {
        case 1:
            cout << "Заповніть таблицю А:" << endl;
            CreateA(sa, amount);
            cout << endl << " Таблиця успішно заповнена!" << endl;
            break;
        case 2:
            cout << "Заповніть таблицю B:" << endl;
            CreateB(sb, amount);
            cout << endl << " Таблиця успішно заповнена!" << endl;
            break;
        case 3:
            cout << "Заповніть таблицю А:" << endl;
            CreateA(sa, amount);
            cout << "Заповніть таблицю B:" << endl;
            CreateB(sb, amount);
            cout << endl << " Таблиці успішно заповнені!" << endl;
            break;
        case 0:
            break;
        }

        if (tableMenu == 1) {
            TableA(sa, amount);
        }
        else if (tableMenu == 2) {
            TableB(sb, amount);
        }
        else if (tableMenu == 3) {
            TableA_B(sa, sb, amount);
        }
        else if (tableMenu != 0) {
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню!" << endl;
        }
    } while (tableMenu != 0);

    return 0;
}
#include <iostream>
#include <fstream>
#include <conio.h>
#include <locale>
#include <iomanip>
#include <codecvt>
#include <string>
#include <chrono>
#include <vector>
#include <sstream>

using namespace std;

string getPath();
string getValidPath();
bool readDatesFromFile(ifstream& file, int& day1, int& month1, int& year1, int& day2, int& month2, int& year2);
bool readRouteFromFile(ifstream& file, string& route);
bool readNameFromFile(const std::string& filename, string& name);
string chooseTheAim();
int calculateDaysBetweenDates(int year1, int month1, int day1, int year2, int month2, int day2);
void createFile(const int& day1, const int& month1, const int& year1, const int& day2, const int& month2, const int& year2, const string& route, int it, string& name);

int main()
{
    setlocale(LC_CTYPE, "ukr");
    cout << "Введіть шлях для введення:" << endl;
    string path = getValidPath();

    ifstream in(path);
    if (!in)
    {
        cout << "Помилка при відкритті файлу." << endl;
        return 0;
    }

    int it = 1;
    string name;
    string route;
    int day1, month1, year1, day2, month2, year2;

    while (true) {
        if (!readDatesFromFile(in, day1, month1, year1, day2, month2, year2))
            break;

        if (!readRouteFromFile(in, route))
            break;

        if (!readNameFromFile(path, name))
            break;

        createFile(day1, month1, year1, day2, month2, year2, route, it, name);
        it++;
    }

    in.close();
    path.clear();

    return 0;
}

string getPath()
{
    string path;

    cin >> path;

    if (path.empty()) {
        return "";
    }
    else {
        return path;
    }
}

string getValidPath() {
    string path;
    ifstream fin;

    while (true) {
        path = getPath();
        if (path.empty()) {
            continue;
        }

        fin.open(path);
        if (fin.is_open()) {
            if (fin.peek() == EOF) {
                cout << "Цей файл порожній, введіть інший шлях.\n";
                continue;
            }
            break;
        }
        cout << "Цього файлу не існує, спробуйте ввести шлях знову: ";
    }

    fin.close();
    return path;
}

bool readDatesFromFile(ifstream& file, int& day1, int& month1, int& year1, int& day2, int& month2, int& year2)
{
    char slash;
    if (!(file >> month1 >> slash >> day1 >> slash >> year1))
        return false;

    if (!(file >> month2 >> slash >> day2 >> slash >> year2))
        return false;

    return true;
}

bool readRouteFromFile(ifstream& file, string& route)
{
    std::string line;
    if (!std::getline(file, line))
        return false;

    size_t dashPos = line.find('"');
    size_t lastQuotePos = line.rfind('"');

    if (dashPos != std::string::npos && lastQuotePos != std::string::npos && dashPos < lastQuotePos)
    {
        route = line.substr(dashPos + 1, lastQuotePos - dashPos - 1);

        //std::cout << "Маршрут: " << route << std::endl;
    }
    else
    {
    }
    return true;
}

bool readNameFromFile(const std::string& filename, string& name)
{
    ifstream file(filename, std::ios_base::binary);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            name = line;
        }
        file.close();
    }
    return true;
}

void createFile(const int& day1, const int& month1, const int& year1, const int& day2, const int& month2, const int& year2, const string& route, int it, string& name)
{
    std::string aim = chooseTheAim();
    int qDays = calculateDaysBetweenDates(year1, month1, day1, year2, month2, day2);
    int q = qDays + 1;
    std::string outputPath;
    std::cout << "Введіть шлях для виведення: ";
    std::cin.ignore();
    std::getline(std::cin, outputPath);

    std::ofstream outFile(outputPath);
    if (!outFile)
    {
        std::cout << "Помилка при відкритті файлу для запису." << std::endl;
        return;
    }

    string spaces(50, ' ');
    outFile << "<html><head><style>"
        "body { font-family: 'Times New Roman', Times, serif; font-size: 10pt; margin-top: -30pt; padding-left: 50pt; padding-right: 50pt; }"
        ".left-align { text-align: left; }"
        ".center { text-align: center; font-family: 'Times New Roman', Times, serif; font-size: 14pt; font-weight: normal; }"
        ".bold { font-weight: bold; }"
        ".justify { text-align: justify; }" // Add the 'justify' class for justifying text
        ".left-text { text-align: left; float: left; }" // Add the 'left-text' class for left-aligned text
        "</style></head><body>"
        "<div class='left-align'>"
        "ТОВ «Текро»<br>"
        "04071, м. Київ, вул. Спаська, буд.5, оф.№ 60<br>"
        "р/р 26007000016975 в ПАТ «Укрсоцбанк», МФО 300023<br>"
        "Код ЗКПО 25409463, ІПН 254094626567<br>"
        "Св-во № 100029248<br><br>"
        "<div class='center'>"
        "<span class='bold'>НАКАЗ</span><br>"
        "про відрядження № " << it << "-" << std::setw(2) << std::setfill('0') << month1 << "/" << (year1 - 2000) << "<br><br>"
        << "<div class='left-text'>" << std::setw(2) << std::setfill('0') << day1 << "." << std::setw(2) << std::setfill('0') << month1 << "." << year1 << " p. м. Київ</div>" << endl
        << "</div>" // Додано символ кінця рядка
        "<div class='left-align justify' style='text-align: justify; width: 100%;'>"
        "<table style='width: 100%;'><tr><td>"
        "<span style='font-size: 14pt;'>Відрядити менеджера ТОВ «Текро» <span style='font-size: 14pt;'>" << "<span  style='font-size: 14pt;'>" << name << "<span style='font-size: 14pt;'> до " << "<span style='font-size: 14pt;'>" << route << " " << aim << "</span><br><br>"
        "<span style='font-size: 14pt;'>Термін відрядження: " << "<span style='font-size: 14pt;'>" << q << "</span> д. (з " << "<span style='font-size: 14pt;'>" << std::setw(2) << std::setfill('0') << day1 << "." << std::setw(2) << std::setfill('0') << month1 << "." << year1 << "</span> по " << "<span style='font-size: 14pt;'>" << std::setw(2) << std::setfill('0') << day2 << "." << std::setw(2) << std::setfill('0') << month2 << "." << year2 << "</span> р.)<br><br>"
        "<span style='font-size: 14pt;'>Транспортний засіб: автомобіль<br><br>"
        "<span style='font-size: 14pt;'>Директор ТОВ «Текро» __________________  Вондроуш Йозеф"
        "</td></tr></table>"
        "</div>"
        "</body></html>";
    outFile.close();

    std::cout << "Файл успішно створено." << std::endl;
}

string chooseTheAim() {
    string goals[] = {
    "для консультування замовників та потенційних клієнтів з питань застосування продукції виробництва ТОВ «Текро» на практиці, а саме: у процесі відгодівлі та утримання тварин.",
    "з метою забезпечення сервісного обслуговування клієнта, надання порад та консультацій з питань використання продукції виробництва «Текро» при годівлі та утриманні тварин. ",
    "для контролю кількості і якості поставленого товару згідно видаткових документів і договорів та отримання замовлення на поставку наступних партій товарів на підприємства замовників. ",
    "для проведення переговорів з метою налагодження постачань товарів на підприємство замовника. ",
    "для налагодження ділових контактів, контролю кількості та якості поставлених товарів згідно видаткових документів та договорів. ",
    "для  контролю кількості і якості поставлених товарів згідно видаткових документів і договорів, а також для обговорення умов і термінів наступних поставок товарів на підприємства замовників, ",
    "для проведення переговорів з керівництвом підприємств стосовно подальшої співпраці. ",
    "для проведення переговорів з метою налагодження співпраці між ТОВ «Текро» та вищезгаданими підприємствами. ",
    "для обговорення питань стосовно співпраці між ТОВ «Текро» та вищезгаданими підприємствами. ",
    "для звіряння взаєморозрахунків та узгодження періодів, протягом яких підприємством будуть погашені прострочені платежі за поставлені товари. ",
    "для проведення переговорів стосовно співпраці, отримання замовлень на наступні поставки дезінфектантів та обговорення строків і умов оплати за поставлені товари. ",
    "для отримання замовлень на наступні поставки товарів на підприємства замовників. ",
    "з метою узгодження поставок товарів на підприємства замовників. ",
    "з метою організації забезпечення структурних підрозділів компанії всіма необхідними для виробництва матеріальними ресурсами та контролю їхнього раціонального використання, а також зберігання на складах організацій. ",
    "для проведення звірки взаємних розрахунків з контрагентами з метою забезпечення достовірності даних бухгалтерського обліку. ",
    "для звіряння та одержання документів. ",
    "з метою контролю документообігу між підприємствами при розробці перспективних та поточних планів у відповідності до загальної стратегії роботи підприємства. ",
    "для отримання інформації від замовників про попит на товарні позиції, ознайомлення замовників з новими пропозиціями стосовно змін асортименту, узгодження умов рекламних та інших маркетингових заходів, що плануються. "
    };

    for (int i = 0; i < 18; i++) {
        cout << i + 1 << ". " << goals[i] << endl;
    }

    int number = 0;
    string input;

    while (number <= 0 || number > 18) {
        cout << "Оберіть мету (введіть число від 1 до 18): ";
        cin >> input;

        // Перевірка, чи введено число
        if (isdigit(input[0])) {
            number = stoi(input);

            if (number < 1 || number > 18) {
                cout << "Невірне число. ";
                number = 0;
            }
        }
        else {
            cout << "Помилка вводу. ";
        }
    }

    return goals[number - 1];
}

int calculateDaysBetweenDates(int year1, int month1, int day1, int year2, int month2, int day2) {
    tm start = { 0, 0, 0, day1, month1 - 1, year1 - 1900 };
    tm end = { 0, 0, 0, day2, month2 - 1, year2 - 1900 };

    time_t startTime = std::mktime(&start);
    time_t endTime = std::mktime(&end);

    if (startTime == -1 || endTime == -1) {
        return -1;
    }

    chrono::duration<int, ratio<60 * 60 * 24>> duration = chrono::duration_cast<chrono::duration<int, ratio<60 * 60 * 24>>>(chrono::system_clock::from_time_t(endTime) - chrono::system_clock::from_time_t(startTime));
   
        return duration.count();
}
#include <iostream>
#include <curl/curl.h>

// Функция для выполнения запроса POST с данными на сайт
int postData(double result) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    std::string data = "login=test&password=test123&result=" + std::to_string(result);

    curl = curl_easy_init();
    if (curl) {
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, "https://calc.itprotect.ru/api/result");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        res = curl_easy_perform(curl);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return (res == CURLE_OK) ? 0 : 1;
    }
    return 1;
}

int main() {
    double num1, num2, result;
    char op;

    // Запрос ввода двух чисел от пользователя
    std::cout << "Введите первое число: ";
    std::cin >> num1;

    std::cout << "Введите второе число: ";
    std::cin >> num2;

    // Запрос операции, которую нужно выполнить
    std::cout << "Введите операцию (+, -, *, /): ";
    std::cin >> op;

    // Выполнение операции и вывод результата
    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        default:
            std::cerr << "Некорректная операция\n";
            return 1;
    }

    std::cout << "Результат: " << result << std::endl;

    // Отправка результата на сайт
    if (postData(result) == 0) {
        std::cout << "Результат успешно отправлен на сайт\n";
    } else {
        std::cerr << "Ошибка при отправке результата на сайт\n";
        return 1;
    }

    return 0;
}

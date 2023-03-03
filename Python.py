import requests

# Запрос ввода двух чисел от пользователя
num1 = float(input("Введите первое число: "))
num2 = float(input("Введите второе число: "))

# Запрос операции, которую нужно выполнить
op = input("Введите операцию (+, -, *, /): ")

# Выполнение операции и вывод результата
if op == "+":
    result = num1 + num2
elif op == "-":
    result = num1 - num2
elif op == "*":
    result = num1 * num2
elif op == "/":
    result = num1 / num2
else:
    print("Некорректная операция")
    exit()

print("Результат: ", result)

# Отправка результата на сайт
url = "https://calc.itprotect.ru/api/result"
data = {"login": "test", "password": "test123", "result": result}
response = requests.post(url, data=data)

if response.status_code == 200:
    print("Результат успешно отправлен на сайт")
else:
    print("Ошибка при отправке результата на сайт")

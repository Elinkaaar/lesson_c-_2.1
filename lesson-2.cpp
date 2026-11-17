/* #include <iostream>
//int main()
//{
///int* p = new int(42);
//std::cout << "value =" << *p << "\n";
//работаем через указатель
//*p = 100;
std::cout << "value" << *p << "\n"; //100

delete p;  //освобождаем память!
p = nullptr; //обнуляем указатель
// защита от случайного пофтороного  делете
return 0;
}
 */

/*
#include <iostream>

void leaky()
{
int* arr = new int[5];
for (int i = 0; i < 5; ++i)
arr[i] = i * 10;
std::cout << "arr[5] = " << arr[3] << "\n";
//забфли делетехъ арр - утечка памяти!
//dфкк (указатель на стеке) умирает.
//а массив в куче остается навсегда
delete[] arr;
arr = nullptr;
}

void dangereous()
{
int* p = new int(7);
delete p; //Память освобождена
delete p; //Двойное удаление - underfinerd behavior
}

int main()
{
leaky();
//правильый ваиант с массивом
int n  = 5;
int* arr =new int [n];
for (int i = 0; i < n; ++i) arr[i] = i + 1;

int sum = 0;
for (int i = 0; i < n; ++i) sum += arr[i];
std::cout << "sum = " << sum << "\n";

delete[] arr; //удаление массива!
arr = nullptr;
//dangerous(); //расскоментируй для того чтобы увидеть как упадет
return 0;
}
*/

/*
#include <iostream> 
#include <memory>

int main()
{
//Шаг 1 создем
// make_unqique выделеям память под инт со значением 42
//и сразу отдает её под управление  unique_ptr.
std::unique_ptr<int> p =std::make_unique<int>(42);
//ШАГ ДВА ПОЛЬЗУЕМС/ КАК ОБЫЧНЫМ уКАЗАТЕЛЕМ
//operator* разыменовывает  Operatоr - >  дает доступ к члеанм.

std::cout << "Значение: " << *p << "\n";
//Шаг 3 можно поменять значение
*p = 100;
std::cout << "новое значение: " << *p << '\n';
//Шаг 4  delete не пишем
// Когда выйдет p из области видимости ( конец main)
//его деструктор сам вызовет delete для inr
return 0;
}
*/


#include <iostream>
#include <memory>

int main()
{
//Шаг 1. Создаем хозяйка для ште со знчением 7
std::unique_ptr<int> owner = std::make_unique<int>(7);
std::cout << "До блока: *owner = " <<*owner << "\n";
//Шаг 2. Открываем блок {} - новая область видимости
{
//Шаг 2а Передаем Владение в новую переменную
//std::move обязателен: unique_ptr нельзя копировать!
std::unique_ptr<int> guest = std::move(owner);
*guest = 99;
std::cout << "В облаке: guest = " << *guest << "\n";
//Шаг 2б Проверяем что old owner теперь пуст!
if (owner)
{
std::cout << "Owner пуст - владение ушло к guest\n";
}
//Шаг 2в guest выйдет из блока -> сработает delete для int
}
if (!owner)
{
std::cout << "После блока: owner  все еще пуст\n";
}


}//здесь guest уничтожаеся, int  в кучеосовбождается!
//Шаг 3 owner все еще существует но уже не владеет ничем.
//Разыменовывать его нельзя - это nullptr


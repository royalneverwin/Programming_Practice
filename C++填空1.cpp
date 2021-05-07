#include <iostream>
#include <vector>
using namespace std;
template <class Iter, class Fun>
void work(Iter begin, Iter end, Fun f)
{
    for (; begin != end; ++begin) f(*begin);
}
int main()
{
    int n, x;
    cin >> n;
    vector<int> a;
    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        a.push_back(x);
    }
    work(a.begin(), a.end(),
         [](int &x)->void
         {
        x /= 2;
         }
    );
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
    cout << endl;
    return 0;
}
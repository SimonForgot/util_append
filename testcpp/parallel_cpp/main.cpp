#include <iostream>
#include <vector>
#include <execution>
#include <algorithm>
#include <chrono>
using namespace std;
void OIIO();
int main(int argc, char *argv[])
{
	auto count = std::numeric_limits<int>::max() / (sizeof(int) * 40);
	cout << "count:" << count << endl; // 13421772
	vector<int> inc(count);
	std::generate(inc.begin(), inc.end(), []()
				  { return rand(); });

	std::vector<int> outc(count);
	//获取当前时间
	auto beforetime = std::chrono::system_clock::now();
	//①直接进行for循环  //6153ms
	/*for (size_t i = 0; i < inc.size(); i++)
		outc[i] = inc[i] * 10;*/
	//②并行算法 //49ms
	// transform(std::execution::par_unseq, inc.begin(), inc.end(), outc.begin(), [](auto i) {return i * 10; });
	//③串行执行 算法  257ms
	// transform(inc.begin(), inc.end(), outc.begin(), [](auto i) {return i * 10; });
	//④串行排序 //17818ms
	// sort(inc.begin(), inc.end());
	//⑤并行排序 //4773ms
	sort(std::execution::par, inc.begin(), inc.end());

	//获取结束时间
	auto aftertime = std::chrono::system_clock::now();

	//得到一个算法耗时
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(aftertime - beforetime).count() << "ms" << endl;

	return 0;
}
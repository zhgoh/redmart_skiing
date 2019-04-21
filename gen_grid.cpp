#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " [size] [max_heights] [filename]";
    return -1;
  }

  std::ofstream ofs {argv[3]};
  if (ofs.bad())
  {
    std::cout << "File creation failed\n";
    return -2;
  }

  auto size = atoi(argv[1]);
  ofs << size << " " << size << std::endl;
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();

  const auto max_height = atoi(argv[2]);
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(0, max_height);

  for (int i = 0; i < size; ++i)
  {
    for (int j = 0; j < size; ++j)
    {
      ofs << distribution(generator) << " ";
    }
    ofs << std::endl;
  }

  return 0;
}

#### build static boost
./bootstrap.sh --prefix=/home/zhangxinlong/app/boost_182 --with-python=/home/zhangxinlong/app/miniconda3/envs/IE37/bin/python3
./b2 cxxflags=-fPIC cflags=-fPIC link=static install 
## 构建
1. 编译`$ mkdir build`
      `$ cd build`
      `$ cmake ..`
      `$ make`
2. 运行`$ ./build/src/unittest/unittest`


## 学习Gtest GMock

1. gtest提供了三种事件机制：
    1. 全局的，所有用例执行前后。`E.g. unittest/main.cc`
    ```cpp
    class FooEnvironment : public testing::Environment {
    public:
        virtual void SetUp() {
            std::cout << "所有用例执行前" << std::endl;
        }
        virtual void TearDown() {
            std::cout << "所有用例执行后" << std::endl;
        }
    };

    int _tmain(int argc, _TCHAR* argv[]) {
        testing::AddGlobalTestEnvironment(new FooEnvironment);
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    ```
    2. TestSuite级别的，在某一批用例中的第一个用例前和最后一个用例后。`E.g. unittest/system1_test.cc`
    ```cpp
    class FooTest : public testing::Test {
     protected:
      static void SetUpTestCase() {
        shared_resource_ = new ;
      }
      static void TearDownTestCase() {
        delete shared_resource_;
        shared_resource_ = NULL;
      }
      // Some expensive resource shared by all tests.
      static T* shared_resource_;
    };

    TEST_F(FooTest, Test1) {
      // you can refer to shared_resource here 
    }
    3. TestCase级别的，每个TestCase前后。`E.g. unittest/system1_test.cc`
    ```cpp
    class FooCalcTest:public testing::Test {
    protected:
        virtual void SetUp() {
            m_foo.Init();
        }
        virtual void TearDown() {
            m_foo.Finalize();
        }

        FooCalc m_foo;
    };

    TEST_F(FooCalcTest, HandleNoneZeroInput) {
        EXPECT_EQ(4, m_foo.Calc(12, 16));
    }

    TEST_F(FooCalcTest, HandleNoneZeroInput_Error) {
        EXPECT_EQ(5, m_foo.Calc(12, 16));
    }
    ```

2. 通过继承Test类，使用`TEST_F`宏，我们可以在案例之间共享一些通用方法，共享资源。简单的case可以用`TEST`

3. Mock的典型方法：
    - 从被mock类派生出一个Mock类，设置方法，将设定好的Mock对象注入到被测类。对于非指针成员变量不适用，因为不能利用基类指针指向子类对象。`E.g. unittest/system1_test.cc`
    ```cpp
    // 被mock类
    class Test {
    public:
        virtual int get();
        virtual bool set(int i);
    private:
        int _i;
    };

    // 被测类
    class App {
    public:
        App(Test* t) : test_(t) {};
        int get();
        bool set(int i);
    private:
        Test* test_;
    };

    // mock类
    class TestMock : public Test {
    public:
        TestMock() : TestMock() {};
        MOCK_METHOD(bool, set, (int i), ());
        MOCK_METHOD(int, get, (), ());
    };

    // 测试
    TEST(App, case1) {
        TestMock test;
        EXPECT_CALL(test, get()).WillOnce(testing::Return(90));

        App a(&test);
        a.set(70);
        EXPECT_EQ(180, a.get());
    }
    ```
    - 覆盖定义：直接定义一个新类，用于替换被mock类，通过宏替换等方式进行替换，例如用宏定义替换类名，将private替换为public等。`E.g. unittest/system2_test.cc`
    ```cpp
    // 被mock类
    class Test {
    public:
        virtual int get();
        virtual bool set(int i);
    private:
        int _i;
    };

    // 被测类
    #define Test TestMock
    #define private publick
    class App {
    public:
        int get();
        bool set(int i);
    private:
        Test test_;
    };

    // mock类
    class TestMock {
    public:
        MOCK_METHOD(int, get, (), ());
        MOCK_METHOD(bool, set, (int i), ());
    };

    // 测试
    TEST(App, case1) {
        App a;
        TestMock& test = a.test_;
        EXPECT_CALL(test, get()).WillOnce(testing::Return(100));
        EXPECT_CALL(test, set(testing::_)).WillOnce(testing::Return(true));
        a.set(50);
        EXPECT_EQ(100, a.get());
    }
    ```
4. gmock的方法：
    ```cpp
      EXPECT_CALL(mock_object, Method(argument-matchers))
          .With(multi-argument-matchers)
          .Times(cardinality)
          .InSequence(sequences)
          .After(expectations)
          .WillOnce(action)
          .WillRepeatedly(action)
          .RetiresOnSaturation();
        // where all clauses are optional, and .InSequence().After  () .WillOnce() can appear any number of times.
    ```
    - EXPECT_CALL：声明一个调用期待，就是我们期待这个对象的这个方法按什么样的逻辑去执行。
    - mock_object：是我们mock的对象，上例中就是TestUser的一个对象。
    - Method：是mock对象中的mock方法，它的参数可以通过argument-matchers规则去匹配。
    - With：是多个参数的匹配方式指定。
    - Times：表示这个方法可以被执行多少次。如果超过这个次数，则按默认值返回了。
    - InSequence：用于指定函数执行的顺序。它是通过同一序列中声明期待的顺序确定的。
    - After：方法用于指定某个方法只能在另一个方法之后执行。
    - WillOnce：表示执行一次方法时，将执行其参数action的方法。一般我们使用Return方法，用于指定一次调用的输出。
    - WillRepeatedly：表示一直调用一个方法时，将执行其参数action的方法。需要注意下它和WillOnce的区别，WillOnce是一次，WillRepeatedly是一直。
    - RetiresOnSaturation：用于保证期待调用不会被相同的函数的期待所覆盖。
    - DoAll：每次发动时执行a1到an的所有动作。
    - SetArgPointee：设置参数。

## GoogleTest使用
下载相关源码，只要编译gtest-all.cc，gmock-all.cc即可。`E.g. third_party/googletest`

# Unit testing and benchmarking framework for embedded systems

This framework is heavily inspired by Google test and benchmark frameworks.

## Supported platforms
- AVR
- PC(Windows / linux)
### Planned support
- STM32
- MSP430

## Usage
### Unit testing

- Every test must return value of `testBase::result`

#### Basic test
```
#include <testcasebasic.h>
#include <testmacros.h>

TEST(testSuite, testCase)
{
    return testBase::result(true);
}
```

More tests will be added eventually.

### Benchmarking

#### Timing backend

Benchmarking require some facility to time benchmarks.
Right now, there are two backends.

- `std::chrono` enabled by CMake option `TIMING_BACKEND=STD`
- AVR backend using Timer/Counter 1 set to count cpu cycles enabled by CMake option `TIMING_BACKEND=AVR`

More backends will be added eventually.

#### Example output
```
suite name/test name              samples         mean       median         q0.5         q0.9        q0.99   total time
       exp/float_std            490011711 2.040768e-08 1.588139e-08 1.588139e-08 1.978769e-08 2.798998e-08           10
       exp/q_16_16              255530943 3.913420e-08 3.557089e-08 3.557089e-08 4.014519e-08 4.094367e-08           10
```

#### Basic benchmark
```
#include <benchmarkbasic.h>
BENCHMARK(exp, float_std)
{
    float in = 5.0f;
    DoNotOptimize(in);
    auto res = std::exp(in);
    DoNotOptimize(res);
}
```

#### Benchmark with fixture

```
#include <benchmarkfixture.h>
class benchmark_TF : public benchmarkBase
{
    using benchmarkBase::benchmarkBase;

protected:
    void setUp() override { std::cout << "setup" << std::endl; }
    void tearDown() override { std::cout << "teardown" << std::endl; }
};

BENCHMARK_F(benchmark_TF, bench, benchF)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
```

#### Templated benchmark

...

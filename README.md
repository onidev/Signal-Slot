# Signal Slot
Signal Slot C++ Pattern

```c++
od::Signal<std::string> signal;
signal.connect([](const std::string& str)
    {
        std::cout << str << '\n';
    });

signal.emit("Hello world!");
```

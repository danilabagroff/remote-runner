# remote-runner

## Тестировалось 
на Mac OS X(BSD), Ubuntu Linux 16.04

## Особенности
Сетевой сервер реализован при помощи платформо-завсисимых интерфейсов epoll(Linux), kqueue(BSD). В случае необходимости, по аналогии, может быть дополнена реализацией Solaris(evport).

## Компиляция
Необходимы clang и cmake
cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
make
sudo make install

## Конфигурация
### /etc/remote-runnerd.conf (Основной конфигурационный файл)
```
[core]
TelnetServer tcp://127.0.0.1:12345
#TelnetServer unix:///tmp/remote-runnerd.sock

SystemLogLevel debug
NetLogLevel debug

SystemLogFile /tmp/remote-runnerd.sys.log
NetLogFile /tmp/remote-runnerd.net.log

SystemLogOutput on
NetLogOutput on

ApplicationListFile /etc/remote-runnerd.app.list
ApplicationTimeout 30
```

### /etc/remote-runnerd.app.list (Список разрешенных к запуску программ)
```
/bin/sleep 10
/bin/ls -la /tmp
```

## Запуск
`Для того чтобы демонизировать процесс воспользуйтесь опцией --background`
```
remote-runnerd --background
```

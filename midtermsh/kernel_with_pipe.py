
import os, sys

READ_TAG = "read"
WRITE_TAG = "write"
EXIT_TAG = "exit"
FORK_TAG = "fork"
EXEC_TAG = "exec"
PIPE_TAG = "pipe"

def kernel(main, args, stdin):
    print("Running process {} with args={}, stdin={}".format(main, args, stdin))
    processes = [(main, args)]
    fd = {}
    fd["main"] = [0, 1]
    while processes:
        (prog, args) = processes.pop()
        (tag, sargs, cont) = prog(*args)
        if tag == READ_TAG:
            res = ""
            if (not (prog.__name__) in fd) or fd[prog.__name__][0] == 0:
                res = stdin[0]
                stdin = stdin[1:]
            else:
                add = os.read(fd[prog.__name__][0], 1024)
                res += add.decode('UTF-8')
            processes.append((cont, [res]))
        elif tag == WRITE_TAG:
            if (not (prog.__name__) in fd) or fd[prog.__name__][1] == 1:
                print("STDOUT: ", sargs[0])
            else:
                os.write(fd[prog.__name__][1], bytes(sargs[0], 'UTF-8'))
            processes.append((cont, []))
        elif tag == EXIT_TAG:
            print("Exit code from {}: {}".format(prog, sargs[0]))
            pass
        elif tag == FORK_TAG:
            processes.append((cont, [1]))
            processes.append((cont, [0]))
        elif tag == EXEC_TAG:
            processes.append((sargs[0], sargs[1:]))
        elif tag == PIPE_TAG:
            r, w = os.pipe()
            fd[sargs[0]] = [0, w]
            fd[sargs[1]] = [r, 1]
            processes.append((cont, []))
        else:
            print("ERROR: No such syscall")

def make_pipe():
    return (PIPE_TAG, ["printer", "reader"], printer)

def printer():
    return (WRITE_TAG, ["hi"], reader)

def reader():
    return (READ_TAG, [], main)
    
def main(line):
    return (WRITE_TAG, [line], exiter)
    
def exiter():
    return (EXIT_TAG, [0], None)

kernel(make_pipe, [], [])
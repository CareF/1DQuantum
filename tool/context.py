#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import os
import sys

os.chdir(os.path.dirname(__file__))

sys.path.insert(0, os.path.abspath(os.path.join(
    os.path.dirname(__file__), '..')))


if __name__ == "__main__":
    print(os.path.abspath(os.path.join(
        os.path.dirname(__file__), '..')))

# vim: ts=4 sw=4 sts=4 expandtab

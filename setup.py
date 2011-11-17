from distutils.core import setup, Extension

readable = Extension('readable',
                    sources = ['readable.c', 'rd_list.c', 'py.c'])

setup (name = 'Readable',
       version = '1.0',
       description = 'Runs the readable algorithm over an HTML page',
       ext_modules = [readable])

#include <Python.h>

#include "readable.h"

static PyObject *
readable_get_article(PyObject *self, PyObject *args, PyObject *kw)
{
    static char *keywords[] = {
        "html",
        "options",
        NULL,
    };

    char *html;
    int options = READABLE_OPTIONS_DEFAULT;
    if (!PyArg_ParseTupleAndKeywords(args, kw, "s|i", keywords, &html, &options)) {
        return NULL;
    }
    char *article_html = readable(html, "", "UTF-8", options);
    if (!article_html) {
        Py_RETURN_NONE;
    }
    PyObject *article = PyUnicode_FromStringAndSize(article_html, strlen(article_html));
    free(article_html);
    return article;
}

static PyMethodDef ReadableMethods[] = {
    { "get_article", (PyCFunction)readable_get_article, METH_VARARGS | METH_KEYWORDS, NULL },
    { NULL, NULL, 0, NULL },
};

PyMODINIT_FUNC
initreadable(void)
{
    PyObject *m;
    m = Py_InitModule("readable", ReadableMethods);
    if (m == NULL) {
        return;
    }
    PyModule_AddIntConstant(m, "STRIP_UNLIKELYS", READABLE_OPTION_STRIP_UNLIKELYS);
    PyModule_AddIntConstant(m, "WEIGHT_CLASSES", READABLE_OPTION_WEIGHT_CLASSES);
    PyModule_AddIntConstant(m, "CHECK_MIN_LENGTH", READABLE_OPTION_CHECK_MIN_LENGTH);
    PyModule_AddIntConstant(m, "CLEAN_CONDITIONALLY", READABLE_OPTION_CLEAN_CONDITIONALLY);
    PyModule_AddIntConstant(m, "REMOVE_IMAGES", READABLE_OPTION_REMOVE_IMAGES);
    PyModule_AddIntConstant(m, "LOOK_HARDER_FOR_IMAGES", READABLE_OPTION_LOOK_HARDER_FOR_IMAGES);
    PyModule_AddIntConstant(m, "DEFAULT_OPTIONS", READABLE_OPTIONS_DEFAULT);
}

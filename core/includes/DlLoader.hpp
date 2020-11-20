/*
** EPITECH PROJECT, 2020
** DlLoader.hpp
** File description:
** DlLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <string>
#include <dlfcn.h>
#include "Exception.hpp"

template<typename T>
class DlLoader {
    public:
        DlLoader(std::string path) {
            char *error;
            _path = path;
            _handle = dlopen(_path.c_str(), RTLD_LAZY);
            if (!_handle) {
                error = dlerror();
                throw Exception(error);
            }
        }

        ~DlLoader() {
            int ret = dlclose(_handle);
            if (ret != 0) {
                throw Exception(dlerror());
            }
        }

        T getInstance(std::string entry) {
            T (*pnt)();
            pnt = reinterpret_cast<T (*)(void)>(dlsym(_handle, entry.c_str()));
            if (pnt == NULL)
                return NULL;
            return pnt();
        }
    protected:
    private:
        void *_handle;
        std::string _path;
};

#endif /* !DLLOADER_HPP_ */

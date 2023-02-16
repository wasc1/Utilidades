#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <locale.h>

void search_eight_files(LPCTSTR path)
{
    TCHAR szDir[MAX_PATH];
    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    _tcscpy_s(szDir,_countof(szDir),path);
    _tcscat_s(szDir,_countof(szDir),TEXT("\\*"));

    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        _tprintf(TEXT("FindFirstFile failed (%d)\n"), GetLastError());
        return;
    }

    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (_tcscmp(ffd.cFileName, TEXT(".")) != 0 &&
                    _tcscmp(ffd.cFileName, TEXT("..")) != 0)
            {
                TCHAR sub_path[MAX_PATH];
                _tcscpy_s(sub_path,_countof(sub_path),path);
                _tcscat_s(sub_path,_countof(sub_path),TEXT("\\"));
                _tcscat_s(sub_path,_countof(sub_path),ffd.cFileName);
                search_eight_files(sub_path);
            }
        }
        else
        {
            if (_tcsstr(ffd.cFileName, TEXT(".eight")) != NULL)
            {
                _tprintf(TEXT("Arquivo .eight encontrado em: %s\\%s\n"), path, ffd.cFileName);
                TCHAR file_path[MAX_PATH];
                _tcscpy_s(file_path,_countof(file_path), path);
                _tcscat_s(file_path,_countof(file_path),TEXT("\\"));
                _tcscat_s(file_path,_countof(file_path),ffd.cFileName);
                if (!DeleteFile(file_path))
                {
                    _tprintf(TEXT("Não foi possível excluir o arquivo: %s\n"), file_path);
                }
                else
                {
                    _tprintf(TEXT("Arquivo excluído com sucesso: %s\n"), file_path);
                }
            }
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);
}

int _tmain(int argc, _TCHAR* argv[])
{

    setlocale(LC_ALL, "Portuguese");

    if (argc != 2)
    {
        _tprintf(TEXT("Uso: %s <caminho da pasta>\n"), argv[0]);
        return 1;
    }

    search_eight_files(argv[1]);
    return 0;
}

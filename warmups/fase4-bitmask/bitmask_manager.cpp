#include <iostream>
#include <bitset>
#include <string>

// Permisos usando bits (cada bit es un permiso)
// Bit 0: Leer (Read)
// Bit 1: Escribir (Write)
// Bit 2: Ejecutar (Execute)
// Bit 3: Borrar (Delete)
// Bit 4: Administrar (Admin)

const int PERM_READ = 1 << 0;    // 1  (00001)
const int PERM_WRITE = 1 << 1;   // 2  (00010)
const int PERM_EXECUTE = 1 << 2; // 4  (00100)
const int PERM_DELETE = 1 << 3;  // 8  (01000)
const int PERM_ADMIN = 1 << 4;   // 16 (10000)

// Verificar si un permiso está activo
bool has_permission(int permissions, int perm)
{
    return (permissions & perm) != 0;
}

// Agregar un permiso
int add_permission(int permissions, int perm)
{
    return permissions | perm;
}

// Quitar un permiso
int remove_permission(int permissions, int perm)
{
    return permissions & ~perm;
}

// Alternar un permiso (si está, lo quita; si no, lo agrega)
int toggle_permission(int permissions, int perm)
{
    return permissions ^ perm;
}

// Mostrar permisos en formato legible
void show_permissions(int permissions)
{
    std::cout << "Permisos: ";

    if (has_permission(permissions, PERM_READ))
        std::cout << "R ";
    else
        std::cout << "- ";

    if (has_permission(permissions, PERM_WRITE))
        std::cout << "W ";
    else
        std::cout << "- ";

    if (has_permission(permissions, PERM_EXECUTE))
        std::cout << "X ";
    else
        std::cout << "- ";

    if (has_permission(permissions, PERM_DELETE))
        std::cout << "D ";
    else
        std::cout << "- ";

    if (has_permission(permissions, PERM_ADMIN))
        std::cout << "A ";
    else
        std::cout << "- ";

    std::cout << "| Valor binario: " << std::bitset<8>(permissions) << std::endl;
}

int main()
{
    std::cout << "=== BITMASK MANAGER ===" << std::endl;
    std::cout << "Gestion de permisos usando operadores de bits\n"
              << std::endl;

    // Empezar sin permisos
    int user_perms = 0;

    // Mostrar permisos iniciales
    std::cout << "Estado inicial:" << std::endl;
    show_permissions(user_perms);
    std::cout << std::endl;

    // Agregar permisos de lectura y ejecución
    std::cout << "Agregando permisos READ y EXECUTE..." << std::endl;
    user_perms = add_permission(user_perms, PERM_READ);
    user_perms = add_permission(user_perms, PERM_EXECUTE);
    show_permissions(user_perms);
    std::cout << std::endl;

    // Agregar permiso de escritura
    std::cout << "Agregando permiso WRITE..." << std::endl;
    user_perms = add_permission(user_perms, PERM_WRITE);
    show_permissions(user_perms);
    std::cout << std::endl;

    // Quitar permiso de ejecución
    std::cout << "Quitando permiso EXECUTE..." << std::endl;
    user_perms = remove_permission(user_perms, PERM_EXECUTE);
    show_permissions(user_perms);
    std::cout << std::endl;

    // Alternar permiso de borrado (agregar)
    std::cout << "Alternando permiso DELETE (agregar)..." << std::endl;
    user_perms = toggle_permission(user_perms, PERM_DELETE);
    show_permissions(user_perms);
    std::cout << std::endl;

    // Alternar permiso de borrado (quitar)
    std::cout << "Alternando permiso DELETE (quitar)..." << std::endl;
    user_perms = toggle_permission(user_perms, PERM_DELETE);
    show_permissions(user_perms);
    std::cout << std::endl;

    // Verificar permisos específicos
    std::cout << "Verificando permisos:" << std::endl;
    std::cout << "  Tiene READ? " << (has_permission(user_perms, PERM_READ) ? "Sí" : "No") << std::endl;
    std::cout << "  Tiene WRITE? " << (has_permission(user_perms, PERM_WRITE) ? "Sí" : "No") << std::endl;
    std::cout << "  Tiene EXECUTE? " << (has_permission(user_perms, PERM_EXECUTE) ? "Sí" : "No") << std::endl;
    std::cout << "  Tiene ADMIN? " << (has_permission(user_perms, PERM_ADMIN) ? "Sí" : "No") << std::endl;

    return 0;
}
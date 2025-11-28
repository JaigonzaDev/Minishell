#!/bin/bash

# Colores para la salida
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "=========================================="
echo "PRUEBAS DE EXIT STATUS - BASH REAL"
echo "=========================================="
echo ""

# Array para almacenar resultados
declare -a tests
declare -a bash_results
declare -a mini_results

# Función para añadir test
add_test() {
    local cmd="$1"
    tests+=("$cmd")
}

# Definir tests
add_test "ls /directorio_inexistente 2>/dev/null"
add_test "cd /directorio_inexistente 2>/dev/null"
add_test "comando_que_no_existe 2>/dev/null"
add_test "pwd > /dev/null"
add_test "true"
add_test "false"
add_test "export VAR=valor"
add_test "export 123INVALID=valor 2>/dev/null"
add_test "unset VAR"
add_test "echo test > /dev/null"
add_test "cat /archivo_inexistente 2>/dev/null"
add_test "/bin/false"
add_test "/bin/true"

# Ejecutar en bash real
echo "Ejecutando comandos en BASH..."
for cmd in "${tests[@]}"; do
    eval "$cmd"
    bash_results+=($?)
done

echo "Bash tests completados."
echo ""
echo "=========================================="
echo "PRUEBAS DE EXIT STATUS - MINISHELL"
echo "=========================================="
echo ""

# Preparar comandos para minishell
mini_input=""
for cmd in "${tests[@]}"; do
    mini_input+="$cmd"$'\n'"echo \$?"$'\n'
done
mini_input+="exit"$'\n'

# Ejecutar en minishell y capturar solo los exit status
mini_output=$(/home/carlos/proyectos/git/dollar/bin/minishell << EOF 2>&1 | grep -E "^[0-9]+$"
$mini_input

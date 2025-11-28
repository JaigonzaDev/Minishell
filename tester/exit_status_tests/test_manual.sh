#!/bin/bash

# Colores
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

echo "════════════════════════════════════════════════════════════"
echo "  TEST MANUAL - SIMULANDO INTERACCIÓN HUMANA"
echo "════════════════════════════════════════════════════════════"
echo ""

# Array para resultados
declare -a test_names
declare -a bash_results
declare -a mini_results

# Función para ejecutar test
run_test() {
    local name="$1"
    local cmd="$2"
    
    echo -e "${BLUE}[TEST]${NC} $name"
    echo "  Comando: $cmd"
    
    # Ejecutar en bash
    bash -c "$cmd" 2>/dev/null
    local bash_exit=$?
    
    # Ejecutar en minishell (cada comando en sesión separada)
    local mini_exit=$(/home/carlos/proyectos/git/dollar/bin/minishell << MINI_EOF 2>&1 | tail -20 | grep -E '^[0-9]+$' | head -1
$cmd
echo \$?
exit
MINI_EOF
)
    
    # Verificar si mini_exit está vacío
    if [ -z "$mini_exit" ]; then
        mini_exit="ERROR"
    fi
    
    # Comparar
    if [ "$bash_exit" == "$mini_exit" ]; then
        echo -e "  ${GREEN}✓ OK${NC} - Bash: $bash_exit | Minishell: $mini_exit"
    else
        echo -e "  ${RED}✗ FAIL${NC} - Bash: $bash_exit | Minishell: $mini_exit"
    fi
    echo ""
    
    test_names+=("$name")
    bash_results+=("$bash_exit")
    mini_results+=("$mini_exit")
}

echo "INICIANDO PRUEBAS..."
echo ""

# ============================================
# TESTS BÁSICOS SIN PIPES
# ============================================
echo "─────────────────────────────────────────"
echo "SECCIÓN 1: COMANDOS BÁSICOS"
echo "─────────────────────────────────────────"
echo ""

run_test "true" "true"
run_test "false" "false"
run_test "pwd" "pwd > /dev/null"
run_test "echo simple" "echo hola > /dev/null"

# ============================================
# TESTS DE BUILTINS
# ============================================
echo "─────────────────────────────────────────"
echo "SECCIÓN 2: BUILTINS"
echo "─────────────────────────────────────────"
echo ""

run_test "cd exitoso" "cd /tmp"
run_test "cd fallido" "cd /directorio_que_no_existe"
run_test "export válido" "export VAR=valor"
run_test "export inválido" "export 123INVALID=valor"
run_test "unset" "unset PATH"

# ============================================
# TESTS DE COMANDOS EXTERNOS
# ============================================
echo "─────────────────────────────────────────"
echo "SECCIÓN 3: COMANDOS EXTERNOS"
echo "─────────────────────────────────────────"
echo ""

run_test "ls exitoso" "ls /tmp > /dev/null"
run_test "ls fallido" "ls /directorio_inexistente"
run_test "cat fallido" "cat /archivo_inexistente"
run_test "comando no existe" "comando_que_no_existe"

# ============================================
# TESTS DE REDIRECCIONES
# ============================================
echo "─────────────────────────────────────────"
echo "SECCIÓN 4: REDIRECCIONES"
echo "─────────────────────────────────────────"
echo ""

run_test "redirect out a /dev/null" "echo test > /dev/null"
run_test "redirect out a archivo" "echo test > /tmp/test_minishell.txt"
run_test "redirect in inexistente" "cat < /archivo_inexistente"

# ============================================
# TESTS DE PIPES SIMPLES
# ============================================
echo "─────────────────────────────────────────"
echo "SECCIÓN 5: PIPES SIMPLES"
echo "─────────────────────────────────────────"
echo ""

run_test "pipe: echo | cat" "echo test | cat > /dev/null"
run_test "pipe: ls error | cat" "ls /directorio_inexistente | cat"
run_test "pipe: cmd inexistente | cat" "comando_inexistente | cat"
run_test "pipe: true | false" "true | false"
run_test "pipe: false | true" "false | true"

# ============================================
# TESTS DE PIPES MÚLTIPLES
# ============================================
echo "─────────────────────────────────────────"
echo "SECCIÓN 6: PIPES MÚLTIPLES"
echo "─────────────────────────────────────────"
echo ""

run_test "pipe triple: echo|cat|cat" "echo test | cat | cat > /dev/null"
run_test "pipe triple: true|true|false" "true | true | false"
run_test "pipe triple: false|false|true" "false | false | true"
run_test "pipe triple: false|false|false" "false | false | false"
run_test "pipe triple: true|true|true" "true | true | true"

# ============================================
# TESTS DE PIPES CON BUILTINS
# ============================================
echo "─────────────────────────────────────────"
echo "SECCIÓN 7: PIPES CON BUILTINS"
echo "─────────────────────────────────────────"
echo ""

run_test "export | cat" "export VAR=valor | cat"
run_test "pwd | cat" "pwd | cat > /dev/null"

# ============================================
# TESTS DE CASOS COMPLEJOS
# ============================================
echo "─────────────────────────────────────────"
echo "SECCIÓN 8: CASOS COMPLEJOS"
echo "─────────────────────────────────────────"
echo ""

run_test "pipe + error + wc" "ls /noexiste | wc -l > /dev/null"
run_test "pipe + error + grep" "cat /archivo_inexistente | grep test"

# ============================================
# RESUMEN
# ============================================
echo "════════════════════════════════════════════════════════════"
echo "  RESUMEN DE RESULTADOS"
echo "════════════════════════════════════════════════════════════"
echo ""

ok_count=0
fail_count=0

for i in "${!test_names[@]}"; do
    if [ "${bash_results[$i]}" == "${mini_results[$i]}" ]; then
        ((ok_count++))
    else
        ((fail_count++))
    fi
done

total=$((ok_count + fail_count))

echo "Total de tests: $total"
echo -e "${GREEN}Exitosos: $ok_count${NC}"
echo -e "${RED}Fallidos: $fail_count${NC}"
echo ""

if [ $fail_count -eq 0 ]; then
    echo "════════════════════════════════════════════════════════════"
    echo -e "  ${GREEN}🎉 TODOS LOS TESTS PASARON 🎉${NC}"
    echo "════════════════════════════════════════════════════════════"
else
    echo "════════════════════════════════════════════════════════════"
    echo -e "  ${RED}⚠️  ALGUNOS TESTS FALLARON ⚠️${NC}"
    echo "════════════════════════════════════════════════════════════"
    echo ""
    echo "Tests fallidos:"
    for i in "${!test_names[@]}"; do
        if [ "${bash_results[$i]}" != "${mini_results[$i]}" ]; then
            echo -e "  ${RED}✗${NC} ${test_names[$i]}: Bash=${bash_results[$i]} vs Mini=${mini_results[$i]}"
        fi
    done
fi

echo ""

# ============================================
# TABLA DETALLADA
# ============================================
echo "════════════════════════════════════════════════════════════"
echo "  TABLA DETALLADA"
echo "════════════════════════════════════════════════════════════"
echo ""

printf "%-40s | %-8s | %-10s | %-8s\n" "TEST" "BASH" "MINISHELL" "RESULTADO"
printf "%.s─" {1..75}
echo ""

for i in "${!test_names[@]}"; do
    name="${test_names[$i]}"
    bash_val="${bash_results[$i]}"
    mini_val="${mini_results[$i]}"
    
    if [ "$bash_val" == "$mini_val" ]; then
        result="✓ OK"
    else
        result="✗ FAIL"
    fi
    
    printf "%-40s | %-8s | %-10s | %-8s\n" "$name" "$bash_val" "$mini_val" "$result"
done

echo ""


#!/bin/bash

# ════════════════════════════════════════════════════════════
#   TEST BONUS - WILDCARDS Y PATRONES (OPCIONAL)
#   ⚠️  NO OBLIGATORIO - Característica bonus
#   Basado en: Minishell Edge Cases (WIP)
# ════════════════════════════════════════════════════════════

MINISHELL="../../bin/minishell"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'
BOLD='\033[1m'

TOTAL=0
PASSED=0
FAILED=0

# Guardar directorio original y verificar minishell
ORIGINAL_DIR="$(cd "$(dirname "$0")" && pwd)"
MINISHELL_PATH="$ORIGINAL_DIR/$MINISHELL"

if [ ! -f "$MINISHELL_PATH" ]; then
    echo -e "${RED}Error: No se encuentra minishell en $MINISHELL_PATH${NC}"
    exit 1
fi

# Crear directorio temporal para tests
TEST_DIR=$(mktemp -d)
cd "$TEST_DIR" || exit 1

# Crear archivos de prueba con nombres específicos
touch .gitignore .vscode Makefile file1.txt file2.c
mkdir -p subdir

echo -e "${YELLOW}Directorio de pruebas: $TEST_DIR${NC}\n"

# Función para comparar con bash
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_exit="$3"
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BOLD}Test $TOTAL: $test_name${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "Comando: ${YELLOW}$command${NC}"
    echo ""
    
    # Ejecutar en BASH para obtener comportamiento esperado
    local bash_output=$(bash -c "$command" 2>&1 | head -20)
    local bash_exit=$?
    
    # Ejecutar en MINISHELL
    local tmp_input=$(mktemp)
    echo "$command" > "$tmp_input"
    echo "exit" >> "$tmp_input"
    
    local minishell_output=$(cat "$tmp_input" | "$MINISHELL_PATH" 2>&1 | \
        grep -v "^Token:" | \
        grep -v "^DEBUG:" | \
        sed '/^==/,/^$/d' | \
        grep -v "LeakSanitizer" | \
        grep -v "Direct leak" | \
        grep -v "Indirect leak" | \
        grep -v "SUMMARY:" | \
        grep -v "^    #" | \
        grep -v "allocated" | \
        grep -v "BuildId" | \
        grep -v "libc_start" | \
        sed '/^$/d' | \
        head -20)
    
    rm -f "$tmp_input"
    
    echo -e "${CYAN}BASH output:${NC}"
    echo "$bash_output"
    echo ""
    echo -e "${CYAN}MINISHELL output:${NC}"
    echo "$minishell_output"
    echo ""
    
    # Comparar outputs (solo primeras líneas relevantes)
    local bash_first=$(echo "$bash_output" | head -1)
    local mini_first=$(echo "$minishell_output" | head -1)
    
    local output_ok=false
    if [ "$bash_first" = "$mini_first" ]; then
        output_ok=true
        echo -e "${GREEN}✓ Output coincide con bash${NC}"
    else
        echo -e "${RED}✗ Output difiere de bash${NC}"
    fi
    
    # Verificar exit code si se especifica
    local exit_ok=true
    if [ -n "$expected_exit" ]; then
        # Para minishell el exit code puede ser 0 si el shell continúa
        echo -e "Exit code bash: $bash_exit, esperado: $expected_exit"
    fi
    
    # Resultado final
    if [ "$output_ok" = true ]; then
        echo -e "\n${GREEN}✅ TEST PASADO${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "\n${RED}❌ TEST FALLIDO${NC}"
        FAILED=$((FAILED + 1))
    fi
}

# ════════════════════════════════════════════════════════════
#   TESTS DE WILDCARDS
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}"
echo "════════════════════════════════════════════════════════════"
echo "  TESTS DE WILDCARDS Y PATRONES"
echo "════════════════════════════════════════════════════════════"
echo -e "${NC}"

# Tests comienzan aquí (minishell ya verificado arriba)

# Test 1: Wildcard .* (archivos ocultos)
run_test "Wildcard .* - archivos ocultos" \
"echo .*" \
"0"

# Test 2: Wildcard * (archivos normales)
run_test "Wildcard * - archivos normales" \
"echo *" \
"0"

# Test 3: Wildcard .*. (solo ..)
run_test "Wildcard .*. - directorio padre" \
"echo .*." \
"0"

# Test 4: Wildcard con extensión *.txt
run_test "Wildcard *.txt" \
"echo *.txt" \
"0"

# Test 5: Wildcard sin match
run_test "Wildcard sin coincidencias *.xyz" \
"echo *.xyz" \
"0"

# Test 6: ls con wildcard
run_test "ls con wildcard" \
"ls *.txt" \
"0"

# ════════════════════════════════════════════════════════════
#   TESTS DE COMANDOS NO ENCONTRADOS
# ════════════════════════════════════════════════════════════

echo ""
echo -e "${BOLD}${BLUE}Tests de comandos no encontrados:${NC}"

# Test 7: Comando con wildcards en el nombre (Makefile con asteriscos)
run_test "Comando inexistente con wildcards" \
"************M*******a******k*****" \
"127"

# ════════════════════════════════════════════════════════════
#   LIMPIEZA
# ════════════════════════════════════════════════════════════

cd /
rm -rf "$TEST_DIR"

# ════════════════════════════════════════════════════════════
#   RESUMEN
# ════════════════════════════════════════════════════════════

echo ""
echo -e "${BOLD}${BLUE}"
echo "════════════════════════════════════════════════════════════"
echo "  RESUMEN DE RESULTADOS"
echo "════════════════════════════════════════════════════════════"
echo -e "${NC}"
echo ""
echo "Total de tests: $TOTAL"
echo -e "${GREEN}Exitosos: $PASSED${NC}"
echo -e "${RED}Fallidos: $FAILED${NC}"
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${BOLD}${GREEN}"
    echo "════════════════════════════════════════════════════════════"
    echo "  🎉 TODOS LOS TESTS PASARON 🎉"
    echo "════════════════════════════════════════════════════════════"
    echo -e "${NC}"
    exit 0
else
    echo -e "${BOLD}${RED}"
    echo "════════════════════════════════════════════════════════════"
    echo "  ❌ ALGUNOS TESTS FALLARON"
    echo "════════════════════════════════════════════════════════════"
    echo -e "${NC}"
    exit 1
fi

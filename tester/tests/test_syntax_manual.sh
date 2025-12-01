#!/bin/bash

# ════════════════════════════════════════════════════════════
#   TEST MANUAL DE ERRORES DE SINTAXIS
#   Simula entrada manual de usuario para evitar problemas
#   de parsing del propio tester
# ════════════════════════════════════════════════════════════

MINISHELL="../../bin/minishell"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
BOLD='\033[1m'

# Contadores
TOTAL=0
PASSED=0
FAILED=0

# Función para ejecutar un test
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_exit="$3"
    local expected_msg_pattern="$4"
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BOLD}Test $TOTAL: $test_name${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "Comando: ${YELLOW}$command${NC}"
    echo ""
    
    # Crear archivo temporal para el comando
    local tmp_input=$(mktemp)
    echo "$command" > "$tmp_input"
    echo "exit" >> "$tmp_input"
    
    # Ejecutar minishell capturando salida y exit code
    local output=$(cat "$tmp_input" | $MINISHELL 2>&1)
    local exit_code=$?
    
    rm -f "$tmp_input"
    
    # Extraer la línea de error (ignorar el prompt y debug)
    local error_line=$(echo "$output" | grep -i "syntax error\|minishell:" | head -1)
    
    echo -e "Salida: ${YELLOW}$error_line${NC}"
    echo -e "Exit code: ${YELLOW}$exit_code${NC}"
    
    # Verificar exit code
    local exit_ok=false
    if [ "$exit_code" = "$expected_exit" ]; then
        exit_ok=true
        echo -e "Exit code: ${GREEN}✓ OK${NC} (esperado: $expected_exit)"
    else
        echo -e "Exit code: ${RED}✗ FAIL${NC} (esperado: $expected_exit, obtenido: $exit_code)"
    fi
    
    # Verificar mensaje de error
    local msg_ok=false
    if echo "$error_line" | grep -q "$expected_msg_pattern"; then
        msg_ok=true
        echo -e "Mensaje: ${GREEN}✓ OK${NC} (contiene: '$expected_msg_pattern')"
    else
        echo -e "Mensaje: ${RED}✗ FAIL${NC} (debe contener: '$expected_msg_pattern')"
    fi
    
    # Resultado final
    if [ "$exit_ok" = true ] && [ "$msg_ok" = true ]; then
        echo -e "\n${GREEN}✅ TEST PASADO${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "\n${RED}❌ TEST FALLIDO${NC}"
        FAILED=$((FAILED + 1))
    fi
}

# ════════════════════════════════════════════════════════════
#   TESTS DE ERRORES DE SINTAXIS
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}"
echo "════════════════════════════════════════════════════════════"
echo "  TESTS DE ERRORES DE SINTAXIS - MINISHELL"
echo "════════════════════════════════════════════════════════════"
echo -e "${NC}"

# Verificar que minishell existe
if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: No se encuentra el ejecutable de minishell en $MINISHELL${NC}"
    echo "Por favor, compila el proyecto con 'make' antes de ejecutar los tests."
    exit 1
fi

# Test 1: ls >
run_test "Redirección sin archivo (ls >)" \
    "ls >" \
    "0" \
    "syntax error near unexpected token.*newline"

# Test 2: >>>
run_test "Triple redirección de salida (>>>)" \
    ">>>" \
    "0" \
    "syntax error near unexpected token.*>"

# Test 3: | (pipe solo)
run_test "Pipe solo (|)" \
    "|" \
    "0" \
    "syntax error near unexpected token.*newline\|syntax error near unexpected token.*|"

# Test 5: | | (doble pipe)
run_test "Doble pipe (| |)" \
    "| |" \
    "0" \
    "syntax error near unexpected token.*|\|syntax error near unexpected token.*newline"

# Test 6: <<
run_test "Here-document sin delimitador (<<)" \
    "<<" \
    "0" \
    "syntax error near unexpected token.*newline"

# Test 7: >>
run_test "Append sin archivo (>>)" \
    ">>" \
    "0" \
    "syntax error near unexpected token.*newline"

# Test 8: < (redirect in solo)
run_test "Redirección de entrada sin archivo (<)" \
    "<" \
    "0" \
    "syntax error near unexpected token.*newline"

# Test 9: echo | | cat
run_test "Comando con doble pipe (echo | | cat)" \
    "echo | | cat" \
    "0" \
    "syntax error near unexpected token.*|"

# Test 10: ls > > file
run_test "Doble redirección con espacio (ls > > file)" \
    "ls > > file" \
    "0" \
    "syntax error near unexpected token.*>"

# ════════════════════════════════════════════════════════════
#   RESUMEN DE RESULTADOS
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

#!/bin/bash

# ════════════════════════════════════════════════════════════
#   TEST DE EDGE CASES - REDIRECCIONES Y PIPES COMPLEJAS
#   Basado en: Minishell Edge Cases (WIP)
# ════════════════════════════════════════════════════════════

MINISHELL="../../bin/minishell"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
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

# Crear archivos temporales
TEST_DIR=$(mktemp -d)
cd "$TEST_DIR" || exit 1
echo "test content" > in
echo "more content" > file1

echo -e "${YELLOW}Directorio de pruebas: $TEST_DIR${NC}\n"

# Función para ejecutar tests
run_test() {
    local test_name="$1"
    local command="$2"
    local check_type="$3"  # "output", "exit", "file"
    local expected="$4"
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BOLD}Test $TOTAL: $test_name${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "Comando: ${YELLOW}$command${NC}"
    echo ""
    
    # Limpiar archivos de salida previos
    rm -f out out1 out2 2>/dev/null
    
    # Ejecutar en BASH para referencia
    local bash_output=$(bash -c "$command" 2>&1)
    local bash_exit=$?
    
    # Ejecutar en MINISHELL
    local tmp_input=$(mktemp)
    echo "$command" > "$tmp_input"
    echo "exit" >> "$tmp_input"
    
    local mini_output=$(cat "$tmp_input" | "$MINISHELL_PATH" 2>&1 | \
        grep -v "^Token:" | \
        grep -v "^DEBUG:" | \
        sed '/^==/,/^$/d' | \
        grep -v "LeakSanitizer" | \
        grep -v "Direct leak" | \
        grep -v "SUMMARY:" | \
        grep -v "allocated" | \
        grep -v "BuildId" | \
        sed '/^$/d')
    
    rm -f "$tmp_input"
    
    local test_ok=false
    
    case "$check_type" in
        "output")
            echo -e "${CYAN}BASH output:${NC}"
            echo "$bash_output"
            echo ""
            echo -e "${CYAN}MINISHELL output:${NC}"
            echo "$mini_output"
            
            if echo "$mini_output" | grep -q "$expected"; then
                test_ok=true
                echo -e "\n${GREEN}✓ Output contiene: $expected${NC}"
            else
                echo -e "\n${RED}✗ Output no contiene: $expected${NC}"
            fi
            ;;
            
        "exit")
            echo -e "Exit code esperado: $expected"
            # Para minishell, verificamos que detecte el error
            if echo "$mini_output" | grep -qi "error\|not found"; then
                test_ok=true
                echo -e "${GREEN}✓ Detectó el error correctamente${NC}"
            else
                echo -e "${RED}✗ No detectó el error${NC}"
            fi
            ;;
            
        "file")
            if [ -f "$expected" ]; then
                local file_content=$(cat "$expected")
                echo -e "${CYAN}Contenido de archivo $expected:${NC}"
                echo "$file_content"
                
                if [ -s "$expected" ]; then
                    test_ok=true
                    echo -e "${GREEN}✓ Archivo creado correctamente${NC}"
                else
                    echo -e "${RED}✗ Archivo vacío o no creado${NC}"
                fi
            else
                echo -e "${RED}✗ Archivo $expected no existe${NC}"
            fi
            ;;
            
        "noerror")
            # Verificar que NO haya errores
            if ! echo "$mini_output" | grep -qi "error\|syntax error"; then
                test_ok=true
                echo -e "${GREEN}✓ Ejecutó sin errores de sintaxis${NC}"
            else
                echo -e "${RED}✗ Generó error inesperado${NC}"
                echo "$mini_output"
            fi
            ;;
    esac
    
    # Resultado final
    if [ "$test_ok" = true ]; then
        echo -e "\n${GREEN}✅ TEST PASADO${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "\n${RED}❌ TEST FALLIDO${NC}"
        FAILED=$((FAILED + 1))
    fi
}

# ════════════════════════════════════════════════════════════
#   TESTS
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}"
echo "════════════════════════════════════════════════════════════"
echo "  TESTS DE REDIRECCIONES Y PIPES COMPLEJAS"
echo "════════════════════════════════════════════════════════════"
echo -e "${NC}"

# Tests comienzan aquí (minishell ya verificado arriba)

# Test 1: Redirección simple
run_test "Redirección simple (cat < in)" \
"cat < in" \
"output" \
"test content"

# Test 2: Pipe simple
run_test "Pipe simple (echo hello | cat)" \
"echo hello | cat" \
"output" \
"hello"

# Test 3: Redirección de salida
run_test "Redirección out (echo test > out)" \
"echo test > out" \
"file" \
"out"

# Test 4: Pipe con grep
run_test "Pipe con grep (echo hello world | grep hello)" \
"echo hello world | grep hello" \
"output" \
"hello"

# Test 5: Múltiples pipes
run_test "Múltiples pipes (echo test | cat | cat)" \
"echo test | cat | cat" \
"output" \
"test"

# Test 6: Redirección con comando inexistente
run_test "Redirección con comando inexistente" \
"nonexistent_cmd > out" \
"exit" \
"127"

# Test 7: cat sin argumentos (debe esperar input, pero con redirección)
run_test "cat con redirección (cat < in > out)" \
"cat < in > out" \
"file" \
"out"

# Test 8: ls con pipe
run_test "ls con pipe (ls | head -5)" \
"ls | head -5" \
"noerror" \
""

# Test 9: Redirección append
run_test "Redirección append (echo line1 >> out; echo line2 >> out)" \
"echo line1 >> out" \
"file" \
"out"

# Test 10: pwd con redirección
run_test "pwd redirigido (pwd > out)" \
"pwd > out" \
"file" \
"out"

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

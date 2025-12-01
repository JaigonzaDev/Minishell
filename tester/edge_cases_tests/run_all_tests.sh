#!/bin/bash

# ════════════════════════════════════════════════════════════
#   MASTER TEST RUNNER - EDGE CASES
#   Ejecuta todos los tests de edge cases
# ════════════════════════════════════════════════════════════

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'
BOLD='\033[1m'

TOTAL_TESTS=0
TOTAL_PASSED=0
TOTAL_FAILED=0

echo -e "${BOLD}${CYAN}"
echo "╔════════════════════════════════════════════════════════════╗"
echo "║          MASTER TEST RUNNER - EDGE CASES                  ║"
echo "╔════════════════════════════════════════════════════════════╗"
echo -e "${NC}\n"

# Array de tests
declare -a TESTS=(
    "test_wildcards.sh:Wildcards y Patrones"
    "test_redirections.sh:Redirecciones y Pipes"
)

# Función para ejecutar un test
run_test_suite() {
    local test_file="$1"
    local test_name="$2"
    
    echo -e "${BOLD}${BLUE}┌────────────────────────────────────────────────────────────┐${NC}"
    echo -e "${BOLD}${BLUE}│  Ejecutando: $test_name${NC}"
    echo -e "${BOLD}${BLUE}└────────────────────────────────────────────────────────────┘${NC}\n"
    
    if [ ! -f "$test_file" ]; then
        echo -e "${RED}✗ Test no encontrado: $test_file${NC}\n"
        return
    fi
    
    # Ejecutar el test
    ./"$test_file" > /tmp/test_output_edge_$$.txt 2>&1
    local exit_code=$?
    
    # Extraer resumen
    local passed=$(grep -oP "Exitosos: \K[0-9]+" /tmp/test_output_edge_$$.txt | tail -1)
    local failed=$(grep -oP "Fallidos: \K[0-9]+" /tmp/test_output_edge_$$.txt | tail -1)
    local total=$(grep -oP "Total de tests: \K[0-9]+" /tmp/test_output_edge_$$.txt | tail -1)
    
    # Acumular totales
    TOTAL_TESTS=$((TOTAL_TESTS + total))
    TOTAL_PASSED=$((TOTAL_PASSED + passed))
    TOTAL_FAILED=$((TOTAL_FAILED + failed))
    
    # Mostrar resultado
    if [ "$exit_code" -eq 0 ]; then
        echo -e "${GREEN}✅ $test_name: $passed/$total tests pasaron${NC}"
    else
        echo -e "${RED}❌ $test_name: $passed/$total tests pasaron ($failed fallidos)${NC}"
    fi
    
    echo -e "${YELLOW}   Ver detalles: cat /tmp/test_output_edge_$$.txt${NC}\n"
    
    rm -f /tmp/test_output_edge_$$.txt
}

# Cambiar al directorio de tests
cd "$(dirname "$0")"

# Ejecutar cada test
for test_entry in "${TESTS[@]}"; do
    IFS=':' read -r test_file test_name <<< "$test_entry"
    run_test_suite "$test_file" "$test_name"
done

# ════════════════════════════════════════════════════════════
#   RESUMEN GLOBAL
# ════════════════════════════════════════════════════════════

echo -e "\n${BOLD}${CYAN}"
echo "╔════════════════════════════════════════════════════════════╗"
echo "║                  RESUMEN GLOBAL                            ║"
echo "╠════════════════════════════════════════════════════════════╣"
printf "║  Total de tests ejecutados: %-30s ║\n" "$TOTAL_TESTS"
printf "║  ${GREEN}Exitosos: %-46s${CYAN} ║${NC}\n" "$TOTAL_PASSED"
printf "║  ${RED}Fallidos: %-47s${CYAN} ║${NC}\n" "$TOTAL_FAILED"
echo "╚════════════════════════════════════════════════════════════╝"
echo -e "${NC}"

# Calcular porcentaje
if [ $TOTAL_TESTS -gt 0 ]; then
    percentage=$((TOTAL_PASSED * 100 / TOTAL_TESTS))
    echo -e "Tasa de éxito: ${BOLD}$percentage%${NC}\n"
fi

# Exit code
if [ $TOTAL_FAILED -eq 0 ]; then
    echo -e "${BOLD}${GREEN}🎉 TODOS LOS TESTS PASARON 🎉${NC}\n"
    exit 0
else
    echo -e "${BOLD}${YELLOW}⚠️  ALGUNOS TESTS FALLARON ⚠️${NC}\n"
    exit 1
fi

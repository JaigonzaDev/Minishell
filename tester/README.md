# 🧪 Suite de Tests - Minishell

Batería completa de tests para validar el comportamiento del minishell comparado con bash.

## 📊 Resumen Ejecutivo

| Directorio | Tests | ✅ Pasando | ❌ Fallando | % Éxito | Estado |
|------------|-------|-----------|-------------|---------|--------|
| **parsing_tests** | 35 | 17 | 18 | 48.5% | 🟡 |
| **edge_cases_tests** | 17 | 11 | 6 | 64.7% | 🟡 |
| **exit_status_tests** | 30 | - | - | - | ⚠️ Timeout |
| **TOTAL** | **52** | **28** | **24** | **53.8%** | 🟡 |

> ⚠️ **Nota**: exit_status_tests tiene problemas de timeout y no se incluye en el total

## 🚀 Ejecución Rápida

```bash
# 🎯 RECOMENDADO: Verificación rápida de bugs (1 minuto)
bash tester/verify_bugs.sh

# Ejecutar TODOS los tests de parsing y expansión
cd tester/parsing_tests && ./run_all_tests.sh

# Ejecutar TODOS los tests de edge cases
cd tester/edge_cases_tests && ./run_all_tests.sh

# Ejecutar tests individuales
cd tester/parsing_tests && ./test_syntax_manual.sh
cd tester/edge_cases_tests && ./test_wildcards.sh
```

## 📚 Documentación Disponible

| Documento | Descripción | Cuándo Usar |
|-----------|-------------|-------------|
| **README.md** | Este archivo - Guía principal | Comenzar aquí |
| **INFORME_BUGS.md** | Análisis detallado de bugs | Para desarrollo/fixes |
| **RESUMEN_EJECUTIVO.md** | Vista ejecutiva completa | Para reportes/management |
| **verify_bugs.sh** | Script de verificación rápida | Para verificar estado actual |

## 📁 Estructura

```
tester/
├── README.md                    # Este archivo
├── INFORME_BUGS.md             # 🐛 Informe detallado de bugs confirmados
│
├── parsing_tests/              # Tests de sintaxis y expansión (35 tests)
│   ├── test_syntax_manual.sh        # ✅ Mensajes de error (10/10 - 100%)
│   ├── test_syntax_exit_code.sh     # ❌ Exit codes (5/15 - 33%)
│   ├── test_expander.sh             # ⚠️ Expansión variables (2/10 - 20%)
│   ├── run_all_tests.sh             # Master runner
│   ├── README.md                    # Documentación específica
│   └── RESULTS.md                   # Resultados detallados
│
├── edge_cases_tests/           # Tests de edge cases (17 tests)
│   ├── test_wildcards.sh            # ❌ Wildcards (2/7 - 28%)
│   ├── test_redirections.sh         # ✅ Redirecciones (9/10 - 90%)
│   ├── run_all_tests.sh             # Master runner
│   └── README.md                    # Documentación específica
│
├── exit_status_tests/          # Tests de exit status (⚠️ Tiene timeout)
│   ├── test_manual.sh
│   └── README.md
│
└── kichkiro-tester/            # Tester externo (terceros)
    └── ...
```

## 🐛 Bugs Críticos Identificados

**Ver análisis completo en**: [`INFORME_BUGS.md`](./INFORME_BUGS.md)

### 🔴 Prioridad Alta (Críticos)

1. **BUG #1: Exit Status = 0 en errores de sintaxis**
   - Afecta: 10 tests
   - `ls >` → debe retornar `$? = 2`, retorna `0`

2. **BUG #2: Wildcards no se expanden**
   - Afecta: 5 tests
   - `echo *` → imprime `*` en lugar de expandir archivos
   - ⚠️ **Verificar si es obligatorio según subject**

3. **BUG #5: Variables inexistentes eliminan palabras**
   - Afecta: 4 tests
   - `echo hello $non_exist world` → imprime solo `hello`

### 🟡 Prioridad Media

4. **BUG #4: Variables con espacios no se colapsan**
   - Afecta: 3 tests
   - `test="  hello  "; echo $test` → mantiene todos los espacios

5. **BUG #3: Sintaxis ${VAR} no soportada**
   - Afecta: 1 test
   - `echo ${USER}` → no imprime nada
   - ⚠️ **Verificar si es obligatorio según subject**

## ✅ Funcionalidades Correctas

- ✅ **Detección de errores de sintaxis** (100%)
- ✅ **Mensajes de error apropiados** (100%)
- ✅ **Redirecciones básicas** (<, >, >>) (90%)
- ✅ **Variables simples** ($VAR, $PATH, $USER, $SHELL)
- ✅ **Variable $?** (exit status del último comando)
- ✅ **Pipes múltiples**

## 📈 Plan de Acción Sugerido

1. **Corregir BUG #1** (exit status) - Impacto: +10 tests → 73% total
2. **Corregir BUG #5** (variables inexistentes) - Impacto: +4 tests → 80% total
3. **Decidir sobre wildcards** (BUG #2) - Verificar subject
4. **Corregir BUG #4** (word splitting) - Impacto: +3 tests → 86% total
5. **Decidir sobre ${VAR}** (BUG #3) - Verificar subject

**Éxito esperado tras fixes**: ~96% (50/52 tests)

## 🔧 Comandos de Verificación Manual

```bash
# BUG #1: Exit status
echo "ls >" | ./bin/minishell; echo $?  # Debe ser 2

# BUG #2: Wildcards
echo "echo *" | ./bin/minishell  # Debe listar archivos

# BUG #3: ${VAR}
echo "echo \${USER}" | ./bin/minishell  # Debe imprimir usuario

# BUG #4: Word splitting
echo "export test='  hello  '; echo \$test" | ./bin/minishell  # Debe colapsar

# BUG #5: Variables inexistentes
echo "echo hello \$non_exist world" | ./bin/minishell  # Debe imprimir "hello world"
```

## 📝 Notas

- Todos los bugs fueron **verificados manualmente** comparando con bash
- Los tests están bien diseñados - no hay falsos positivos
- Memory leaks detectados por sanitizer (revisar después de bugs funcionales)
- Algunos tests pueden depender de features opcionales del subject

## 🤝 Contribuir

Para añadir nuevos tests:
1. Crear script en el directorio apropiado
2. Seguir formato de tests existentes
3. Actualizar `run_all_tests.sh` del directorio
4. Ejecutar y documentar resultados

---

**Última actualización**: 1 de Diciembre de 2025  
**Tests totales**: 52 (excluyendo exit_status_tests con timeout)  
**Éxito actual**: 53.8%  
**Éxito proyectado**: ~96% tras correcciones

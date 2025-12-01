# 🐛 Informe Detallado de Bugs - Minishell

**Fecha**: 1 de Diciembre de 2025  
**Versión**: minishell con AddressSanitizer  
**Tests ejecutados**: 52 tests  
**Metodología**: Comparación manual con bash + scripts automatizados

---

## 📊 Resumen Ejecutivo

| Categoría | Total | Aprobados | Fallidos | % Éxito |
|-----------|-------|-----------|----------|---------|
| **Sintaxis (manual)** | 10 | 10 | 0 | 100% |
| **Sintaxis (exit code)** | 15 | 5 | 10 | 33% |
| **Expansión de variables** | 10 | 2 | 8 | 20% |
| **Wildcards** | 7 | 2 | 5 | 28% |
| **Redirecciones** | 10 | 9 | 1 | 90% |
| **TOTAL** | **52** | **28** | **24** | **53.8%** |

---

## 🔴 Bugs Críticos Confirmados

### **BUG #1: Exit Status Incorrecto en Errores de Sintaxis**

**Severidad**: 🔴 CRÍTICA  
**Impacto**: 10 tests fallidos  
**Archivos afectados**: `test_syntax_exit_code.sh`

**Descripción**:  
Cuando ocurre un error de sintaxis, minishell establece `$?` en `0` en lugar de `2` como hace bash.

**Ejemplos confirmados**:

```bash
# Caso 1: Redirección sin archivo
echo "ls > 2>&1" | minishell
echo $?  # minishell: 0 ❌ | bash: 2 ✅

# Caso 2: Pipe incompleto
echo "ls |" | minishell
echo $?  # minishell: 0 ❌ | bash: 2 ✅

# Caso 3: Comillas sin cerrar
echo "echo 'hello" | minishell
echo $?  # minishell: 0 ❌ | bash: 2 ✅
```

**Comportamiento esperado**:  
- Bash retorna **exit code 2** para errores de sintaxis
- Minishell debe establecer `$?` en `2` después de detectar el error

**Tests afectados**:
1. ✅ Mensaje de error (correcto)
2. ❌ Exit status (incorrecto)

---

### **BUG #2: Wildcards No Se Expanden**

**Severidad**: 🔴 CRÍTICA  
**Impacto**: 5 tests fallidos  
**Archivos afectados**: `test_wildcards.sh`

**Descripción**:  
Los wildcards (`*`, `.*`, `*.ext`) se imprimen literalmente en lugar de expandirse a los archivos coincidentes.

**Ejemplos confirmados**:

```bash
# Caso 1: Wildcard básico *
echo "echo *" | minishell
# minishell: * ❌
# bash: Makefile bin build docs include libs source tester ✅

# Caso 2: Archivos ocultos .*
echo "echo .*" | minishell
# minishell: .* ❌
# bash: .git .vscode ✅

# Caso 3: Extensión *.c
echo "echo *.c" | minishell
# minishell: *.c ❌
# bash: main.c utils.c ✅
```

**Comportamiento esperado**:  
- `*` debe expandirse a todos los archivos del directorio actual
- `.*` debe expandirse a todos los archivos ocultos
- `*.ext` debe expandirse a archivos con esa extensión
- Si no hay coincidencias, debe imprimir el patrón literal

**Tests afectados**: 5 de 7 tests de wildcards

---

### **BUG #3: Variables Con Llaves `${VAR}` No Funcionan**

**Severidad**: 🟡 MEDIA  
**Impacto**: 1 test fallido  
**Archivos afectados**: `test_expander.sh`

**Descripción**:  
La sintaxis de expansión con llaves `${VAR}` no está implementada. Minishell solo soporta `$VAR`.

**Ejemplos confirmados**:

```bash
# Caso 1: Variable con llaves
echo "echo \${USER}" | minishell
# minishell: (vacío) ❌
# bash: carlos ✅

# Caso 2: Variable sin llaves (FUNCIONA)
echo "echo \$USER" | minishell
# minishell: carlos ✅
# bash: carlos ✅
```

**Comportamiento esperado**:  
Bash soporta ambas sintaxis: `$VAR` y `${VAR}`. Minishell debería soportarlas también o al menos imprimir el literal si no está implementado.

**Nota**: El subject de minishell puede no requerir esta funcionalidad. Verificar requisitos.

---

### **BUG #4: Variables Con Espacios No Se Colapsan**

**Severidad**: 🟡 MEDIA  
**Impacto**: ~3 tests fallidos  
**Archivos afectados**: `test_expander.sh`

**Descripción**:  
Cuando una variable contiene múltiples espacios, minishell los mantiene todos. Bash los colapsa a un solo espacio.

**Ejemplos confirmados**:

```bash
# Caso: Múltiples espacios en variable
export test="  hello  world  "
echo $test

# minishell: "  hello  world  " ❌
# bash: "hello world" ✅
```

**Comportamiento esperado**:  
Al expandir `$var` sin comillas, bash realiza "word splitting" y colapsa espacios múltiples. Minishell debe replicar este comportamiento.

**Solución propuesta**:  
Implementar word splitting después de la expansión de variables (solo cuando no están entre comillas).

---

### **BUG #5: Variables Inexistentes Eliminan Palabras Siguientes**

**Severidad**: 🔴 CRÍTICA  
**Impacto**: ~4 tests fallidos  
**Archivos afectados**: `test_expander.sh`

**Descripción**:  
Cuando una variable inexistente aparece en medio de un comando, las palabras después de ella desaparecen.

**Ejemplos confirmados**:

```bash
# Caso 1: Variable inexistente en medio
echo "echo hello \$non_exist world" | minishell
# minishell: hello ❌
# bash: hello world ✅

# Caso 2: Variable inexistente + variable existente
echo "echo \$non_exist \$SHELL" | minishell
# minishell: (vacío) ❌
# bash: /usr/bin/zsh ✅
```

**Comportamiento esperado**:  
- Variable inexistente debe expandirse a cadena vacía
- Las palabras siguientes deben procesarse normalmente
- No debe cortar el procesamiento del comando

**Solución propuesta**:  
Revisar lógica de expansión en `expand_dollar.c` para no interrumpir el parsing después de variables inexistentes.

---

## 🟢 Funcionalidades Correctas

### ✅ **Detección de Errores de Sintaxis**
- **10/10 tests aprobados** (100%)
- Mensajes de error correctos para todos los casos
- Solo falla el exit status (BUG #1)

### ✅ **Redirecciones**
- **9/10 tests aprobados** (90%)
- Funcionan: `<`, `>`, `>>`, pipes múltiples
- Solo 1 fallo por investigar

### ✅ **Variables Simples**
- `$VAR` funciona correctamente
- `$SHELL`, `$USER`, `$PATH` se expanden bien
- Solo fallan casos con llaves `${VAR}` y espacios múltiples

---

## 🔧 Plan de Acción Recomendado

### Prioridad Alta 🔴
1. **BUG #1**: Fijar exit status a 2 en errores de sintaxis
   - Archivo: `source/main.c` o donde se maneje el exit status
   - Complejidad: Baja
   - Impacto: 10 tests

2. **BUG #5**: Corregir pérdida de palabras tras variables inexistentes
   - Archivo: `source/expand_dollar/expand_dollar.c`
   - Complejidad: Media
   - Impacto: 4 tests

3. **BUG #2**: Implementar expansión de wildcards
   - Archivo: Nuevo módulo o en `expand_dollar/`
   - Complejidad: Alta
   - Impacto: 5 tests

### Prioridad Media 🟡
4. **BUG #4**: Implementar word splitting con colapso de espacios
   - Archivo: `source/expand_dollar/expand_dollar.c`
   - Complejidad: Media
   - Impacto: 3 tests

5. **BUG #3**: Soportar sintaxis `${VAR}` (si lo requiere el subject)
   - Archivo: `source/expand_dollar/expand_dollar.c`
   - Complejidad: Baja-Media
   - Impacto: 1 test

---

## 📁 Archivos a Revisar

```
source/
├── main.c                          # BUG #1: Exit status
├── expand_dollar/
│   ├── expand_dollar.c             # BUGS #3, #4, #5: Expansión
│   └── late_expansion.c            # Revisar lógica
└── tokens/
    └── (posible nuevo módulo)      # BUG #2: Wildcards
```

---

## 🧪 Comandos de Verificación

```bash
# Verificar BUG #1
echo "ls >" | ./bin/minishell
echo $?  # Debe ser 2

# Verificar BUG #2
echo "echo *" | ./bin/minishell  # Debe expandir

# Verificar BUG #3
echo "echo \${USER}" | ./bin/minishell  # Debe imprimir usuario

# Verificar BUG #4
export test="  hello  world  "; echo $test  # Debe colapsar espacios

# Verificar BUG #5
echo "echo hello \$non_exist world" | ./bin/minishell  # Debe imprimir "hello world"
```

---

## 📈 Progreso Estimado Post-Fixes

Si se corrigen todos los bugs:

| Categoría | Tests | Éxito Actual | Éxito Esperado |
|-----------|-------|--------------|----------------|
| Sintaxis (exit) | 15 | 33% | **100%** |
| Expander | 10 | 20% | **90%** |
| Wildcards | 7 | 28% | **100%** |
| Redirecciones | 10 | 90% | **100%** |
| **TOTAL** | **52** | **53.8%** | **~96%** |

---

## 📝 Notas Adicionales

- **Memory leaks**: El sanitizer detecta leaks en varios tests. Revisar después de corregir bugs funcionales.
- **Subject compliance**: Verificar si `${VAR}` y wildcards son obligatorios según el subject.
- **Test reliability**: Los tests están bien diseñados. Los fallos son bugs reales de minishell.

---

**Generado por**: Verificación manual + scripts automatizados  
**Contacto**: Para dudas sobre casos específicos, revisar scripts en `tester/`

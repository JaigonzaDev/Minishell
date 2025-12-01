# 📓 Jupyter Notebook - Minishell Interactive Tests

Notebook interactivo para ejecutar y validar tests de minishell uno por uno.

## 🚀 Cómo usar

### 1. Instalar Jupyter (si no lo tienes)

```bash
pip install jupyter notebook
# o
pip3 install jupyter notebook
```

### 2. Iniciar Jupyter Notebook

```bash
cd notebook
jupyter notebook
```

Esto abrirá tu navegador con la interfaz de Jupyter.

### 3. Abrir el notebook

- Haz clic en `minishell_tests.ipynb`
- Ejecuta las celdas una por una con `Shift + Enter`
- O ejecuta todas con `Cell > Run All`

## 📋 Contenido del Notebook

### Setup (Celda 1-2)
- Configuración inicial
- Funciones auxiliares para ejecutar comandos en minishell
- Verificación de que minishell está compilado

### Tests por Categoría

#### 1️⃣ Exit Codes (Celdas 3-7)
- Verifica códigos de salida: `2` para syntax errors, `0` para éxito, `1` para errores
- Tests individuales para cada caso

#### 2️⃣ Expansión de Variables (Celdas 8-14)
- Variables vacías
- Variables consecutivas `$a$b`
- Variables posicionales `$0`, `$1`, etc.
- `$?` (exit status)
- Word splitting

#### 3️⃣ Redirecciones y Pipes (Celdas 15-18)
- Redirección de salida `>`
- Pipes simples y múltiples `|`
- Errores a stderr

#### 4️⃣ Tests Personalizados (Celda 19)
- Ejecuta tus propios comandos
- Modifica la variable `custom_command`

#### 5️⃣ BONUS - Wildcards (Celda 20)
- ⚠️ **OPCIONAL**: Tests de wildcards `*`, `?`, `[...]`

## 🔧 Cómo funciona

El notebook usa `subprocess` para ejecutar minishell con comandos pasados por stdin:

```python
# Crear archivo temporal con comandos
echo "comando" > /tmp/input.txt
echo "exit" >> /tmp/input.txt

# Ejecutar minishell
./minishell < /tmp/input.txt
```

Esto permite:
- ✅ Ejecutar un comando y que minishell termine automáticamente
- ✅ Capturar stdout, stderr y exit code
- ✅ Comparar con bash para validar comportamiento

## 📊 Ventajas del Notebook

- **Interactivo**: Ejecuta tests uno por uno
- **Visual**: Colores y formato claro
- **Flexible**: Modifica tests sobre la marcha
- **Educativo**: Entiende cada test paso a paso
- **Debugging**: Ejecuta solo los tests que necesitas

## 🎯 Uso típico

1. Compilar minishell: `make` en el directorio raíz
2. Abrir el notebook: `jupyter notebook`
3. Ejecutar Setup (primeras 2 celdas)
4. Ejecutar tests individuales o todos
5. Modificar y experimentar con comandos personalizados

## 🐛 Troubleshooting

### "Minishell not found"
```bash
cd ../../..  # Ir al directorio raíz
make         # Compilar minishell
```

### "Jupyter not found"
```bash
pip install --user jupyter notebook
```

### Tests timeout
- Los comandos tienen timeout de 5 segundos
- Si minishell se cuelga, se cancela automáticamente

## 📝 Alternativa: Scripts Shell

Si prefieres ejecutar todos los tests de una vez:
```bash
cd ..
./run_all.sh
```

El notebook es ideal para:
- Debugging de tests específicos
- Experimentación interactiva
- Aprendizaje y comprensión paso a paso

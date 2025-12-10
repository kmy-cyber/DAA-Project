#!/bin/bash

set -e

GREEN="\e[32m"
YELLOW="\e[33m"
RED="\e[31m"
BLUE='\033[0;34m'
NC="\e[0m"


echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}      DAA Project Setup & Run${NC}"
echo -e "${BLUE}========================================${NC}"
echo ""

check_requirements() {
    echo -e "${YELLOW}Comprobando dependencias...${NC}"

    # check Python
    if ! command -V python3 &> /dev/null; then
        echo -e "${RED}✗ Python3 no está instalado${NC}"
        exit 1
    else
        echo -e "${GREEN}✓ Python3 OK${NC}"
    fi

    # check g++
    if ! command -V g++ &> /dev/null; then
        echo -e "${RED}✗ g++ (C++) no está instalado${NC}"
        exit 1
    else
        echo -e "${GREEN}✓ g++ OK${NC}"
    fi
}

open_pdf() {
    local pdf="report/informe_daa.pdf"
    if [[ -f "$pdf" ]]; then
        echo -e "${GREEN}Abriendo informe...${NC}"
        xdg-open "$pdf"
    else
        echo -e "${RED}No se encontró el PDF en ${pdf}${NC}"
    fi
}

run_code() {
    check_requirements
    echo -e "${GREEN}Ejecutando programa...${NC}"
    python3 src/main.py
}


echo "========== MENÚ =========="
echo "1) Leer informe (PDF)"
echo "2) Ejecutar el código"
echo "3) Salir"
echo ""
read -p "Elige una opción: " option


case $option in

    1)  open_pdf ;;
    2)  run_code ;;
    3)  echo -e "${GREEN}Hasta luego!${NC}"; exit 0 ;;
    *)
        echo -e "${RED}Opción inválida${NC}"
        exit 1
        ;;
esac

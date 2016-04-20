#!/bin/bash
##################################
##   declaration des couleurs   ##
##################################

WHITE="\033[0m"
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
MAGENTA="\033[0;35m"
CYAN="\033[0;36m"

BOLD="\033[1m"
BRED="\033[1;31m"
BGREEN="\033[1;32m"
BYELLOW="\033[1;33m"
BBLUE="\033[1;34m"
BMAGENTA="\033[1;35m"
BCYAN="\033[1;36m"

##################################
##   declaration des variables  ##
##################################

#FTEMP="$HOME/.config/norme/.temp"
TMP=".norm_tmp"

NB_ERROR=0


function print_error() # imprime le message d'erreur
{
    echo -e $BRED"Erreur: $CYAN`basename $1`: $WHITE$2"
}

function print_triche() # imprime le message de triches
{
    echo -e $BCYAN"/***************************************\\ $WHITE"
    echo -e $BCYAN"|            $BRED TRICHE$BCYAN                     "
    echo -n "| "
    print_error $1 "$2          $BCYAN"
    echo -e $BCYAN"\                                       /$WHITE"
    echo -e $BCYAN"****************************************$WHITE"
}

function function_length() # verifie la longueur des fonctions (plus de 25 lignes)
{
    local VAR=`cat $1 | pcregrep -vM "^[a-z]+.*\(.*\)$\n\{(.*\n){1,26}^\}$" | grep -vE "(/\*|^\*\*|\*/|^#)" | pcregrep -vM "(^\n$){2,}" |  grep -Eo "[a-zA-Z_0-9]+\(.*\)$" | head -n1`
    if [[ ! -z $VAR ]]; then
	local TMP=`cat $1 | pcregrep -vM "^[a-z]+.*\(.*\)$\n\{(.*\n){1,26}^\}$" | grep -vE "(/\*|^\*\*|\*/|^#)" | pcregrep -vM "(^\n$){2,}"| pcregrep -vM "(^\}$\n+|\n+^\{$)"| wc -l`
	if [[ $TMP -gt 25 ]]; then
	    print_error $1 "$VAR: fonction de plus de 25 lignes"
	    NB_ERROR=$(($NB_ERROR + 1))
	fi
    fi
}

function nb_functions() # verifie le nombre de fonctins (plus de 5 par fichier)
{
    local NB_LINE=`cat $1 | grep "^[a-z]\{1,\}.*)$" | wc -l`
    if [[ $NB_LINE -gt 5 ]]
    then
	print_error $1 "$NB_LINE fonctions"
	NB_ERROR=$((NB_ERROR + 1))
    fi
}

function function_params() # verifie le nombre de parametres des fonctions (plus de 4)
{
    local VAR=`grep -nE "^[a-z]{1,}.*\((.*,){4,}.*\)$" $1`
    if [[ ! -z $VAR ]]; then
	local LINE=`echo $VAR | tr ":" " " | awk '{print $1}'`
	local FUNCT=`echo $VAR | tr ":" " " | grep -oE "[a-zA-Z_0-9]+\("`
	print_error $1 "ligne $LINE $FUNCT...): too many parameters"
	NB_ERROR=$((NB_ERROR + 1))
    fi
}

function last_carac() # verifie les 80 colonnes
{
    local RES=`cat $1 | grep -nE ".*\s+$" | grep -v "*\*" | awk '{print $1}'`
    for LINE in $RES
    do
	print_error $1 "ligne `echo -n $LINE | sed "s/.$//"` espace en fin de ligne"
	NB_ERROR=$((NB_ERROR + 1))
    done
}


clear
options $*

#if [[ ! -d $HOME/.config/norme/.temp ]]; then
#    mkdir -p $FTEMP
#fi

find $PWD -name "*.c" | grep -v \# > $TMP

for SFILE in `cat $TMP`; do
    echo -e "Scan : "$BOLD"`basename $SFILE`"$WHITE
    nb_functions $SFILE
    last_carac $SFILE
    function_length $SFILE
    function_params $SFILE
done

if [[ $NB_ERROR -eq 0 ]]; then
    echo -e $BGREEN"Vous avez fait 0 fautes de norme"
elif [[ $NB_ERROR -eq 1 ]]; then
    echo -e $BRED"Vous avez fait $NB_ERROR faute de norme."
else
    echo -e $BRED"Vous avez fait $NB_ERROR fautes de norme."
fi
echo -ne $WHITE
#rm -rf $FTEMP
rm $TMP

set nocompatible
set showcmd
set helplang=cn
set shiftwidth=4
set sw=4
set backspace=2
"Enable syntax highlight
syntax enable
"Enable highlight by theme
syntax on
set number
set history=1000
set autoindent
set expandtab
set smartindent
set tabstop=4
set showmatch
set ruler
set incsearch
set winaltkeys=no
set hlsearch
autocmd BufReadPost *
            \ if line("'\"")>0&&line("'\"")<=line("$") |
            \ exe "normal g'\"" |
            \ endif


"Enable filetype detect,
"launch plugin by filetype
"apply different indent by filetype
filetype on
filetype plugin on
filetype indent on

"Set MapLeader
let mapleader=";"

set completeopt=longest,menu
"plugin settings
let Tlist_Show_One_File=1           "Only show current file tags
let Tlist_Exit_OnlyWindow=1        
let TList_Inc_Winwidth=0
let Tlist_use_Right_Window=1
let Tlist_File_Fold_Auto_Close=1
let Tlist_Auto_Open=0

nnoremap<Leader>tl :TlistToggle<CR>
nnoremap<Leader>fl :NERDTreeToggle<CR>
nnoremap<C-h> <C-w>h
nnoremap<C-k> <C-w>k
nnoremap<C-l> <C-w>l
nnoremap<C-j> <C-w>j
imap jj <Esc>j

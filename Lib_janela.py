''' 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

'''

import pygame

class Janela():
    def __init__(self,largura,altura,titulo,r,g,b, iniciar_fullscreen=False):
        self.largura = largura
        self.altura = altura
        self.titulo = titulo
        self.janela = None
        self.cor = [r,g,b]
        self.font = None
        self.iniciar_fullscreen = iniciar_fullscreen

        #variaveis de botoes
        self.offset = 0  # Offset inicial dos dados
        self.numBotoes = 8
        self.listaBotoes = []
        self.listaBotoesEstado = []
        self.tipo_botao = ""
        self.x_botao = 0
        self.y_botao = 0
        self.l_botao = 0
        self.h_botao = 0
        self.separacao_y = 0
        self.margem_y_superior = 0
        self.margem_y_inferior = 0
        self.vel_scroll = 0
        self.cor_botao = [122, 122, 122]
        self.totalPokemons = 0

         # Caixa de texto
        self.input_active = False
        self.input_text = ""
        self.input_color_active = (255, 255, 255) 
        self.input_color_inactive = (200, 200, 200)
        self.input_color = self.input_color_inactive
        
        # Não definimos fixo, vamos calcular após iniciar a janela
        self.input_rect = None

        # Botão voltar - posição e tamanho serão ajustados após iniciar
        self.btn_voltar = None
        self.btn_voltar_color = (100,100,100)
        self.btn_voltar_pressed = False
        self.btn_voltar_ativado = False

        # Variáveis para os botões de salvar e carregar
        self.btn_save = None
        self.btn_load = None
        self.btn_save_pressed = False
        self.btn_load_pressed = False
        self.btn_save_load_ativado = False
        
    def Iniciar(self):
        pygame.font.init()  # Inicializa o subsistema de fontes

        # Se a flag for True, pega o tamanho ideal do monitor
        if self.iniciar_fullscreen:
            info = pygame.display.Info()
            self.largura = info.current_w
            self.altura = info.current_h

        self.janela = pygame.display.set_mode((self.largura,self.altura), pygame.RESIZABLE)
        
        if self.janela is None:
            raise RuntimeError("Falha ao inicializar a janela.")
        pygame.display.set_caption(self.titulo)
        self.janela.fill(self.cor)
        self.font = self.DefinirFont()

        # Define posições do botão voltar e da caixa de pesquisa
        # Botão voltar no canto superior esquerdo (0,0) com 0.2 da largura e 0.05 da altura
        self.btn_voltar = pygame.Rect(0, 0, 0.2*self.largura, 0.05*self.altura)

        # Caixa de pesquisa no topo, começando em 0.3 da largura
        self.input_rect = pygame.Rect(0.3*self.largura, 0, 200, 32)  # Largura ajustada depois se necessário

        # Ajusta a posição inicial dos botões um pouco abaixo do topo
        # Por exemplo, depois do botão voltar e da caixa de busca, começamos os botões da pokedex mais abaixo
        # Digamos que começamos a listar os pokemons a partir de 0.15 da altura
        self.y_botao = 0.15 * self.altura

    def Fechar(self):
        pygame.display.quit()  # Encerra a exibição
        pygame.font.quit()  # Encerra o subsistema de fontes
        pygame.quit()  # Encerra o Pygame completamente

    def TelaCheia(self):
        pygame.display.toggle_fullscreen()

    def GetJanelaDimensoes(self):
        return pygame.display.get_window_size()

    def SetConfigBotoes(self, numBotoes = 6, float_margem_x = 0.05, float_separacao_y = 0.05, float_margem_y = 0.05, float_margem_inferior = 0.05, float_margem_x_direita = 0):
        self.cor_botao = [122, 122, 122]
        self.numBotoes = numBotoes
        self.separacao_y = float_separacao_y * self.altura
        self.margem_y_superior = float_margem_y * self.altura
        self.margem_y_inferior = float_margem_inferior * self.altura
        self.x_botao =  float_margem_x * self.largura
        self.y_botao = self.margem_y_superior
        if float_margem_x_direita == 0:
            self.l_botao = self.largura - self.x_botao * 2
        else:
            self.l_botao = self.largura - self.x_botao - float_margem_x_direita * self.largura

        if self.numBotoes > 1:
            self.h_botao = (self.altura - self.margem_y_superior - self.margem_y_inferior - (numBotoes-1)* self.separacao_y ) / numBotoes
        else:
            self.h_botao = 0

    def SetConfigBotaoUnico(self, x,y,l,h, r=235, g=64, b=52):
        self.cor_botao = [ r, g, b]
        self.numBotoes = 1
        self.separacao_y = 0
        self.margem_y_superior = 0
        self.margem_y_inferior = 0
        self.x_botao =  x
        self.y_botao = y
        self.l_botao = l
        self.h_botao = h

    def GetBotaoPos(self, i):
        if i < len(self.listaBotoes):
            botao = self.listaBotoes[i]
            # Normalizar para [0,1]
            nx = botao.x / self.largura
            ny = botao.y / self.altura
            return (nx, ny)
        return (0.0, 0.0)

    def AdicionarBotoes(self, tipo, quantidade, totalPokemons, offset = 0):
        self.totalPokemons = totalPokemons
        self.LimparBotoes()
        self.offset = offset
        qnt_botoes = len(self.listaBotoes)
        while qnt_botoes < quantidade:
            self.listaBotoes.append(pygame.Rect(self.x_botao, self.y_botao + qnt_botoes*(self.h_botao+self.separacao_y), self.l_botao, self.h_botao))
            self.listaBotoesEstado.append(False)
            qnt_botoes = len(self.listaBotoes)
        
        self.tipo_botao = tipo

    def SetBotaoEstado(self, index, estado):
        if 0 <= index < len(self.listaBotoesEstado):
            self.listaBotoesEstado[index] = estado

    def getEstadosBotoes(self):
        return self.listaBotoesEstado
    
    def GetOffset(self):
        return self.offset

    def DesenharBotoes(self):
        if self.tipo_botao == "pokedex":
            # k é um fator arbitrário para controlar a sensibilidade
            k = 0.6

            # Calcula o deslocamento baseado na velocidade atual.
            # Quanto maior a vel_scroll, maior o deslocamento.
            deslocamento = self.vel_scroll * 0.005 * self.altura * k

            # Cálculo do espaço vertical total para o loop
            espaco_vertical_total = self.h_botao * 0.93 # + self.separacao_y

            limite_superior = self.margem_y_superior
            limite_inferior = self.altura - self.margem_y_inferior

            # Se há um deslocamento significativo, movemos os botões
            if abs(self.vel_scroll) > 0.1:  # Limite para considerar se ainda há inércia
                mover = 0
                


                self.listaBotoes[0].move_ip(0, deslocamento)
                # Verifica se o primeiro saiu por cima
                if self.listaBotoes[0].top < limite_superior and self.offset < self.totalPokemons - self.numBotoes + 0:
                    mover = +1
                    self.offset += 1
                    # Reposiciona o primeiro botão para ficar dentro da tela 
                    self.listaBotoes[0].move_ip(0, espaco_vertical_total)

                # Verifica se o primeiro saiu por baixo
                elif self.listaBotoes[self.numBotoes-1].top > limite_inferior:
                    mover = -1
                    if self.offset > 0:
                        self.offset -= 1
                    # Reposiciona o primeiro botão para ficar dentro da tela
                    self.listaBotoes[0].move_ip(0, -espaco_vertical_total)
                
                

                
                for botao in self.listaBotoes[1:]:
                    botao.move_ip(0, deslocamento + espaco_vertical_total*mover)
                        

                # Agora reduzimos a velocidade para simular inércia diminuindo
                # Multiplicar por um fator < 1 reduz a velocidade gradualmente.
                # Ajuste o fator conforme desejar um efeito mais suave ou mais brusco.
                if self.offset < 0 or self.offset > self.totalPokemons - self.numBotoes: ##TESTANDO AQuiiiiiiiiiiiiii
                    self.vel_scroll = 0
                self.vel_scroll *= 0.90
            else:
                # Se a velocidade é muito pequena, zeramos para não ficar tremendo.
                self.vel_scroll = 0

        # Desenha os botões
        for i, botao in enumerate(self.listaBotoes):
            cor_usada = self.cor_botao
            if self.listaBotoesEstado[i]:
                cor_usada = [155, 155, 155]
            pygame.draw.rect(self.janela, cor_usada, botao)


    def LimparBotoes(self):
        self.listaBotoes = []
        self.listaBotoesEstado = []

    def DesenharImagem(self, imagem, pos_x, pos_y):
        self.janela.blit(imagem, (pos_x, pos_y))

    def ProcessarEventos(self):
        if self.janela is None:
            raise RuntimeError("A janela não foi inicializada. Certifique-se de chamar 'IniciarJanela' antes de usar 'ProcessarEventos'.")
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False  # Sinal para encerrar o loop
            if event.type == pygame.MOUSEBUTTONDOWN :
                mouse_x, mouse_y = event.pos  # posição do mouse no momento do clique
                if event.button == 1:  # Somente botão esquerdo
                    for i in range(len(self.listaBotoes)):
                        if self.listaBotoes[i].collidepoint((mouse_x, mouse_y)):
                            self.listaBotoesEstado[i] = True
                        else:
                            self.listaBotoesEstado[i] = False

                    # Botões de Salvar e Carregar
                    if self.btn_save_load_ativado:
                        if self.btn_save and self.btn_save.collidepoint((mouse_x, mouse_y)):
                            self.btn_save_pressed = True
                        if self.btn_load and self.btn_load.collidepoint((mouse_x, mouse_y)):
                            self.btn_load_pressed = True

                if event.button == 3:  # Somente botão direito
                    for i in range(len(self.listaBotoes)):
                        if self.listaBotoes[i].collidepoint((mouse_x, mouse_y)):
                            self.listaBotoesEstado[i] = True
                        else:
                            self.listaBotoesEstado[i] = False

                # Verifica se clicou na caixa de input
                if self.input_rect.collidepoint((mouse_x, mouse_y)):
                    self.input_active = True
                    self.input_color = self.input_color_active
                else:
                    self.input_active = False
                    self.input_color = self.input_color_inactive

                # Verifica clique no botão voltar (se estiver ativo)
                if self.btn_voltar_ativado and self.btn_voltar and self.btn_voltar.collidepoint((mouse_x, mouse_y)):
                    self.btn_voltar_pressed = True

            if event.type == pygame.MOUSEWHEEL and self.tipo_botao == "pokedex":
                # Ajusta a velocidade do scroll.
                # Ex: se y > 0, rolando para "cima", diminui a posição (velocidade negativa)
                # se y < 0, rolando para "baixo", aumenta a posição (velocidade positiva).
                    # Limita a rolagem superior e inferior
                    if event.y < 0 and self.offset < self.totalPokemons - self.numBotoes:  # Rolando para baixo
                        self.vel_scroll -= 1.5
                    elif event.y > 0 and self.offset > 0:  # Rolando para cima
                        self.vel_scroll += 1.5

            # Eventos de teclado para input
            if event.type == pygame.KEYDOWN and self.input_active:
                if event.key == pygame.K_BACKSPACE:
                    self.input_text = self.input_text[:-1]
                else:
                    self.input_text += event.unicode

            else:
                pass
            
        return True

    def Atualizar(self):
        #self.ProcessarEventos()  # Processa eventos antes de atualizar
        
        pygame.display.flip()  # Atualiza a exibição
        self.janela.fill(self.cor)  # Preenche a janela com a cor de fundo

       # Desenha o botão voltar, se ativo
        if self.btn_voltar_ativado and self.btn_voltar:
            pygame.draw.rect(self.janela, self.btn_voltar_color, self.btn_voltar)
            text_surface = self.font.render("Voltar", True, (255, 255, 255))
            self.janela.blit(text_surface, (self.btn_voltar.x + 10, self.btn_voltar.y + 10))

        # Desenha os botões de Salvar e Carregar, se ativos
        if self.btn_save_load_ativado:
            pygame.draw.rect(self.janela, (122, 150, 122), self.btn_save)  # cinza + verde
            text_surface = self.font.render("Salvar", True, (255, 255, 255))
            self.janela.blit(text_surface, (self.btn_save.x + 90, self.btn_save.y + 15))
            
            pygame.draw.rect(self.janela, (237, 206, 147), self.btn_load)  # cinza + laranja
            text_surface = self.font.render("Carregar", True, (255, 255, 255))
            self.janela.blit(text_surface, (self.btn_load.x + 85, self.btn_load.y + 15))

        # Desenha a caixa de texto
        # Se não estiver ativa e/ou estiver vazia, exibe "pesquisar" como placeholder
        if self.input_active:
            # Caixa branca
            self.input_color = self.input_color_active
        else:
            # Caixa cinza
            self.input_color = self.input_color_inactive

        
        if self.tipo_botao == "pokedex":
            pygame.draw.rect(self.janela, self.input_color, self.input_rect)

            if self.input_text.strip() == "":
                # Se vazio, mostra placeholder
                placeholder_text = "pesquisar"
                text_surface = self.font.render(placeholder_text, True, (100, 100, 100))
            else:
                # Mostra o texto digitado
                text_surface = self.font.render(self.input_text, True, (0, 0, 0))
            
            self.janela.blit(text_surface, (self.input_rect.x+5, self.input_rect.y+5))
            # Ajusta largura do retângulo com base no texto digitado
            self.input_rect.w = max(200, text_surface.get_width()+10)

    def DesenharRect(self, x, y, l, h, r, g, b):
        rect = pygame.Rect(x, y, l, h)
        pygame.draw.rect(self.janela, [r,g,b], rect)

    def DesenharTipo(self, x, y, l, h, tipo):
        cor = [255,255,255]
        if tipo == "Fire":
            cor = [255,162,0]
        elif tipo == "Water":
            cor = [0, 145, 255]
        elif tipo ==  "Grass":
            cor = [133, 224, 108]
        elif tipo == "Electric":
            cor = [240, 191, 43]
        elif tipo == "Ice":
            cor = [156, 229, 247]
        elif tipo == "Poison":
            cor = [143, 77, 148]
        elif tipo == "Fairy":
            cor = [252, 192, 250]
        elif tipo == "Fighting":
            cor = [143, 14, 4]
        elif tipo == "Bug":
            cor = [176, 224, 92]
        elif tipo == "Ghost":
            cor = [128, 101, 148]
        elif tipo == "Steel":
            cor = [176, 176, 176]
        elif tipo == "Dragon":
            cor = [86, 67, 143]
        elif tipo == "Dark":
            cor = [89, 47, 1]
        elif tipo == "Psychic":
            cor = [237, 2, 167]
        elif tipo == "Rock":
            cor = [191, 152, 11]
        elif tipo == "Ground":
            cor = [204, 184, 131]
        elif tipo == "Flying":
            cor = [186, 169, 218]
        elif tipo == "Normal":
            cor = [209, 204, 178]
        else:
            cor = [0, 255, 10]

        espacoLetras = len(tipo)
        if espacoLetras == 3:
            x_texto = x + espacoLetras * 14.5
        elif espacoLetras == 4:
            x_texto = x + espacoLetras * 11
        elif espacoLetras == 5:
            x_texto = x + espacoLetras * 7.5
        elif espacoLetras == 6:
            x_texto = x + espacoLetras * 5.5
        elif espacoLetras == 7:
            x_texto = x + espacoLetras * 4
        elif espacoLetras == 8:
            x_texto = x + espacoLetras * 3

        rect = pygame.Rect(x, y, l, h)
        pygame.draw.rect(self.janela, cor, rect)
        espacoLetras = len(tipo)
        text_surface = self.font.render(tipo, True, (255, 255, 255))
        self.janela.blit(text_surface, (x_texto, y+5))

    def DefinirFont(self,tamanho_font = 26): #sem alteracao de font implementada
        return pygame.font.Font(None, tamanho_font)
    
    def Escrever(self,text, x, y, color=(255, 255, 255)):
    # Renderiza o texto
        text_surface = self.font.render(text, True, color)
    
    # Desenha o texto na tela na posição (x, y)
        self.janela.blit(text_surface, (x, y))

    # Métodos novos para manipular a botao de voltar
    def AtivarBackButton(self, ativo: bool):
        self.btn_voltar_ativado = ativo

    def getBtnVoltaEstado(self):
        estado = self.btn_voltar_pressed
        self.btn_voltar_pressed = False
        return estado

    # Métodos novos para manipular a caixa de entrada
    def AtivarInputBox(self, ativo: bool):
        self.input_active = ativo
        if ativo:
            self.input_color = self.input_color_active
        else:
            self.input_color = self.input_color_inactive

    def AtivarSaveLoadButtons(self, ativo: bool):
        """Ativa ou desativa os botões de salvar e carregar."""
        self.btn_save_load_ativado = ativo
        if ativo:
            # Define as posições e tamanhos dos botões salvar e carregar
            largura_botao = 0.3 * self.largura
            altura_botao = 0.08 * self.altura
            self.btn_save = pygame.Rect(0.3 * self.largura, 0.9*self.altura, largura_botao, altura_botao)
            self.btn_load = pygame.Rect(0.65 * self.largura, 0.9*self.altura, largura_botao, altura_botao)
        else:
            self.btn_save = None
            self.btn_load = None

    def getSaveLoadStates(self):
        """Retorna os estados dos botões salvar e carregar."""
        states = [self.btn_save_pressed, self.btn_load_pressed]
        # Reseta os estados após a leitura
        self.btn_save_pressed = False
        self.btn_load_pressed = False
        return states

    def GetInputText(self):
        return self.input_text

    def LimparInputText(self):
        self.input_text = ""


def CarregarImagem(caminho_imagem, largura, altura):
    image = pygame.image.load(caminho_imagem)
    image = pygame.transform.scale(image, (largura, altura))
    return image

def IniciarPygame():
    pygame.init() #importante!
STDOUT.sync = true # DO NOT REMOVE

class Node
  attr_accessor :coordinate,
                :adjacent_nodes,
                :owner, # . - empty, O,o - mine, X,x - opponent
                :level, # 0 - empty, otherwise level of unit occupying
                :tower,
                :mine

  def initialize(coordinate, owner)
    @coordinate = coordinate
    @owner = owner
    @adjacent_nodes = []
    @level = 0
    @tower = false
    @mine = false
  end

  def add_edge(node)
    @adjacent_nodes << node
  end
end

class Graph
  attr_accessor :nodes

  def initialize
    @nodes = {}
  end

  def add_node(node)
    @nodes[node.coordinate] = node
  end

  def add_edges(node1, node2)
    @nodes[node1].add_edge(@nodes[node2]) if @nodes[node1].owner != '#' && @nodes[node2].owner != '#'
  end
end

class Frontier
  attr_accessor :my_tile_list, :opponent_tile_list

  def initialize
    @my_tile_list = []
    @opponent_tile_list = []
  end

  def add_my_tile(coordinates)
    @my_tile_list << coordinates
  end

  def add_opponent_tile(coordinates)
    @opponent_tile_list << coordinates
  end
end

class Units
  attr_accessor :my_unit_list, :opponent_unit_list

  def initialize
    @my_unit_list = {}
    @opponent_unit_list = {}
  end

  def add_unit(owner, id, level, x, y)
    if owner.zero?
      @my_unit_list[id] = { level: level, x: x, y: y }
    else
      @opponent_unit_list[id] = { level: level, x: x, y: y }
    end
  end
end

class Buildings
  attr_accessor :my_buildings, :opponent_buildings

  def initialize
    @my_buildings = []
    @opponent_buildings = []
  end

  def add_building(owner, type, x, y)
    if owner.zero?
      @my_buildings << { type: type, x: x, y: y }
    else
      @opponent_buildings << { type: type, x: x, y: y }
    end
  end
end

class Resources
  attr_accessor :my_gold, :my_income, :opponent_gold, :opponent_income
end

class Mines
  attr_accessor :mines_list

  def initialize
    @mines_list = []
  end

  def add_mine(x, y)
    @mines_list << { x: x, y: y }
  end
end

def breadth_first_search(source, destination)
  border_line = []
  came_from = {}

  came_from[source] = nil
  border_line << source

  until border_line.empty?
    current_node = border_line.shift

    return came_from if current_node == destination

    @graph_map.nodes[current_node].adjacent_nodes.each do |node|
      # next if !node.level.zero? && node.owner == 'O'

      unless came_from.include? node.coordinate
        came_from[node.coordinate] = current_node
        border_line << node.coordinate
      end
    end
  end
  nil
end

def find_path(source, destination)
  came_from = breadth_first_search(source, destination)

  return nil  if came_from.nil?

  current = destination
  path = []
  while current != source
    path << current
    current = came_from[current]
  end

  path.reverse
end

def create_graph_map(map)
  (0..11).each do |y|
    row = map[y].split('')
    (0..11).each do |x|
      node = Node.new(x.to_s + ' ' + y.to_s, row[x])
      @graph_map.add_node(node)
    end
  end
end

def update_graph_map(map)
  (0..11).each do |y|
    row = map[y].split('')
    (0..11).each do |x|
      @graph_map.nodes[x.to_s + ' ' + y.to_s].owner = row[x]
      @graph_map.nodes[x.to_s + ' ' + y.to_s].level = 0
      @graph_map.nodes[x.to_s + ' ' + y.to_s].tower = false
      @graph_map.nodes[x.to_s + ' ' + y.to_s].mine = false
    end
  end
end

def construct_graph_map_edges
  (0..11).each do |y|
    (0..11).each do |x|
      current_node = x.to_s + ' ' + y.to_s
      if y - 1 >= 0
        neighbour_node = x.to_s + ' ' + (y - 1).to_s
        @graph_map.add_edges(current_node, neighbour_node)
      end
      if y + 1 <= 11
        neighbour_node = x.to_s + ' ' + (y + 1).to_s
        @graph_map.add_edges(current_node, neighbour_node)
      end
      if x - 1 >= 0
        neighbour_node = (x - 1).to_s + ' ' + y.to_s
        @graph_map.add_edges(current_node, neighbour_node)
      end
      if x + 1 <= 11
        neighbour_node = (x + 1).to_s + ' ' + y.to_s
        @graph_map.add_edges(current_node, neighbour_node)
      end
    end
  end
end

def update_frontiers
  @frontier.my_tile_list.clear
  @frontier.opponent_tile_list.clear
  (0..11).each do |y|
    (0..11).each do |x|
      owner = @graph_map.nodes[x.to_s + ' ' + y.to_s].owner
      if %w[o O].include? owner
        @graph_map.nodes[x.to_s + ' ' + y.to_s].adjacent_nodes.each do |node|
          if %w[X x .].include? node.owner
            @frontier.add_my_tile(x: x, y: y)
            break
          end
        end
      elsif %w[x X].include? owner
        @graph_map.nodes[x.to_s + ' ' + y.to_s].adjacent_nodes.each do |node|
          if %w[O o .].include? node.owner
            @frontier.add_opponent_tile(x: x, y: y)
            break
          end
        end
      end
    end
  end
end

def update_units
  @units.my_unit_list.clear
  @units.opponent_unit_list.clear

  unit_count = gets.to_i
  unit_count.times do
    owner, unit_id, level, x, y = gets.split(' ').collect(&:to_i)
    @units.add_unit(owner, unit_id, level, x, y)
    @graph_map.nodes[x.to_s + ' ' + y.to_s].level = level
  end
end

def update_buildings
  @buildings.my_buildings.clear
  @buildings.opponent_buildings.clear

  building_count = gets.to_i
  building_count.times do
    owner, building_type, x, y = gets.split(' ').collect(&:to_i)
    @buildings.add_building(owner, building_type, x, y)

    update_tower_data(x.to_s + ' ' + y.to_s, true) if building_type == 2
    @graph_map.nodes[x.to_s + ' ' + y.to_s].mine = true if building_type == 1
  end
end

def update_tower_data(tile, value)
  @graph_map.nodes[tile].tower = value
  @graph_map.nodes[tile].adjacent_nodes.each do |node|
    node.tower = value
  end
end

def update_resources
  @resources.my_gold = gets.to_i
  @resources.my_income = gets.to_i
  @resources.opponent_gold = gets.to_i
  @resources.opponent_income = gets.to_i
end

def lvl1_tactics
  commands = ''
  lvl_1_units = @units.my_unit_list.select { |_id, unit| unit[:level] == 1 }

  lvl_1_units.each do |id, unit|
    tile = explore_tile(unit[:x].to_s + ' ' + unit[:y].to_s, unit[:level])
    next if tile.nil?

    commands += format('MOVE %<id>s %<tile>s;', id: id, tile: tile)
    @graph_map.nodes[unit[:x].to_s + ' ' + unit[:y].to_s].level = 0
    @graph_map.nodes[tile].owner = 'O'
    @graph_map.nodes[tile].level = unit[:level]
    update_frontiers
  end

  while lvl_1_units.length < MAX_LVL1_UNITS && @resources.my_gold >= 10
    tile = get_lvl1_frontier_tile
    break if tile.nil?

    commands += format('TRAIN 1 %<tile>s;', tile: tile)
    STDERR.puts lvl_1_units
    lvl_1_units[tile] = {}
    @graph_map.nodes[tile].owner = 'O'
    @graph_map.nodes[tile].level = 1
    @resources.my_gold -= 10
    @resources.my_income -= 1
    update_frontiers
  end

  commands
end

def lvl2_tactics
  commands = ''

  lvl_2_units = @units.my_unit_list.select { |_id, unit| unit[:level] == 2 }

  lvl_2_units.each do |id, unit|
    tile = lvl2_attack_tile(unit[:x].to_s + ' ' + unit[:y].to_s, unit[:level])
    next if tile.nil?

    commands += format('MOVE %<id>s %<tile>s;', id: id, tile: tile)
    @graph_map.nodes[unit[:x].to_s + ' ' + unit[:y].to_s].level = 0
    @graph_map.nodes[tile].owner = 'O'
    @graph_map.nodes[tile].level = unit[:level]
    update_frontiers
  end

  max_two_at_time = 0
  while lvl_2_units.length < MAX_LVL2_UNITS && @resources.my_gold >= 20
    tile = get_lvl2_frontier_tile
    break if tile.nil? || max_two_at_time == 2

    commands += format('TRAIN 2 %<tile>s;', tile: tile)
    max_two_at_time += 1
    lvl_2_units[tile] = {}
    @graph_map.nodes[tile].owner = 'O'
    @graph_map.nodes[tile].level = 2
    @resources.my_gold -= 20
    @resources.my_income -= 4
    update_frontiers
  end

  commands
end

def lvl3_tactics
  commands = ''
  lvl_3_units = @units.my_unit_list.select { |_id, unit| unit[:level] == 3 }

  lvl_3_units.each do |id, unit|
    tile = lvl3_attack_tile(unit[:x].to_s + ' ' + unit[:y].to_s, unit[:level])
    next if tile.nil?

    commands += format('MOVE %<id>s %<tile>s;', id: id, tile: tile)
    @graph_map.nodes[unit[:x].to_s + ' ' + unit[:y].to_s].level = 0
    @graph_map.nodes[tile].owner = 'O'
    @graph_map.nodes[tile].level = unit[:level]
    update_frontiers
  end

  while lvl_3_units.length < MAX_LVL3_UNITS && @resources.my_gold >= 30 && @resources.my_income >= 20
    tile = get_lvl3_frontier_tile
    break if tile.nil?

    commands += format('TRAIN 3 %<tile>s;', tile: tile)
    lvl_3_units[tile] = {}
    @graph_map.nodes[tile].owner = 'O'
    @graph_map.nodes[tile].level = 3
    @resources.my_gold -= 30
    @resources.my_income -=20
    update_frontiers
  end
  commands
end

def build_mines
  commands = ''
  my_mines_list = @buildings.my_buildings.select { |building| building[:type] == 1 }
  return commands if my_mines_list.length >= MAX_MINES

  @mines.mines_list.each do |mine|
    break if @resources.my_gold <= 20
    next unless @graph_map.nodes[mine[:x].to_s + ' ' + mine[:y].to_s].level.zero?
    next if @graph_map.nodes[mine[:x].to_s + ' ' + mine[:y].to_s].mine
    next if %w[X x .].include? @graph_map.nodes[mine[:x].to_s + ' ' + mine[:y].to_s].owner

    commands += format('BUILD MINE %<x>d %<y>d;', x: mine[:x], y: mine[:y])
    @graph_map.nodes[mine[:x].to_s + ' ' + mine[:y].to_s].mine = true
    @resources.my_gold -= 20 + my_mines_list.length * 4
    @resources.my_income += 4
  end
  commands
end

def build_towers
  commands = ''
  my_tower_list = @buildings.my_buildings.select { |building| building[:type] == 2 }
  return commands if my_tower_list.length >= MAX_TOWERS

  if my_tower_list.length.zero?
    hq = @buildings.my_buildings.select { |building| building[:type].zero? }
    tower_x = 1
    tower_y = 1
    unless hq[0][:x].zero?
      tower_x = 10
      tower_y = 10
    end

    commands += format('BUILD TOWER %<x>d %<y>d;', x: tower_x, y: tower_y)
    @graph_map.nodes[tower_x.to_s + ' ' + tower_y.to_s].tower = true
    @resources.my_gold -= 15
    @resources.my_income += 4
  end
  commands
end

def give_order
  commands = ''

  commands += lvl1_tactics if @current_turn <= CHANGE_TACTICS_TURN

  if @current_turn >= CHANGE_TACTICS_TURN
    commands += build_towers
    commands += lvl3_tactics
    commands += lvl2_tactics
    commands += build_mines
    # commands += passive_explore
  end
  puts commands + 'WAIT;'
end

def get_lvl3_frontier_tile
  @frontier.my_tile_list.each do |tile|
    this_node = @graph_map.nodes[tile[:x].to_s + ' ' + tile[:y].to_s]
    next unless this_node.level.zero?

    this_node.adjacent_nodes.each do |node|
      return this_node.coordinate if node.owner == 'X' && (node.tower || node.level >= 2)
    end
  end
  nil
end

def get_lvl2_frontier_tile
  @frontier.my_tile_list.each do |tile|
    this_node = @graph_map.nodes[tile[:x].to_s + ' ' + tile[:y].to_s]
    next unless this_node.level.zero?

    this_node.adjacent_nodes.each do |node|
      return this_node.coordinate if node.owner == 'X' && !node.tower
    end
  end
  get_lvl1_frontier_tile
end

def get_lvl1_frontier_tile
  @frontier.my_tile_list.each do |tile|
    @graph_map.nodes[tile[:x].to_s + ' ' + tile[:y].to_s].adjacent_nodes.each do |node|
      return node.coordinate if node.owner == '.' && !node.tower
    end
  end
  @frontier.my_tile_list.each do |tile|
    node = @graph_map.nodes[tile[:x].to_s + ' ' + tile[:y].to_s]
    if node.level.zero? && !node.tower
      return tile[:x].to_s + ' ' + tile[:y].to_s
    end
  end
  nil
end

def lvl2_attack_tile(tile, unit_lvl)
  @graph_map.nodes[tile].adjacent_nodes.each do |node|
    next unless can_move?(node.coordinate, unit_lvl)
    return node.coordinate if ['X', 'x'].include? node.owner
  end
  enemy_hq = @buildings.opponent_buildings.select { |building| building[:type].zero? }
  path = find_path(tile, enemy_hq[0][:x].to_s + ' ' + enemy_hq[0][:y].to_s)

  return enemy_hq[0][:x].to_s + ' ' + enemy_hq[0][:y].to_s unless can_move?(path[0], unit_lvl)

  path[0]
end

def lvl3_attack_tile(tile, unit_lvl)
  @graph_map.nodes[tile].adjacent_nodes.each do |node|
    next unless can_move?(node.coordinate, unit_lvl)
    return node.coordinate if ['X', 'x'].include? node.owner
  end
  enemy_hq = @buildings.opponent_buildings.select { |building| building[:type].zero? }
  path = find_path(tile, enemy_hq[0][:x].to_s + ' ' + enemy_hq[0][:y].to_s)

  return enemy_hq[0][:x].to_s + ' ' + enemy_hq[0][:y].to_s unless can_move?(path[0], unit_lvl)

  path[0]
end

def explore_tile(tile, unit_lvl)
  @graph_map.nodes[tile].adjacent_nodes.each do |node|
    next unless can_move?(node.coordinate, unit_lvl)
    return node.coordinate if ['X', 'x', '.'].include? node.owner
  end
  enemy_hq = @buildings.opponent_buildings.select { |building| building[:type].zero? }
  path = find_path(tile, enemy_hq[0][:x].to_s + ' ' + enemy_hq[0][:y].to_s)

  return enemy_hq[0][:x].to_s + ' ' + enemy_hq[0][:y].to_s unless can_move?(path[0], unit_lvl)

  path[0]
end

def can_move?(tile, unit_lvl)
  case unit_lvl
  when 1
    return false unless @graph_map.nodes[tile].level.zero?
    return false if @graph_map.nodes[tile].tower
  when 2
    return false if !@graph_map.nodes[tile].level.zero? && @graph_map.nodes[tile].owner == 'O'
    return false if @graph_map.nodes[tile].level >= 2
    return false if @graph_map.nodes[tile].tower
  when 3
    return false if !@graph_map.nodes[tile].level.zero? && @graph_map.nodes[tile].owner == 'O'
  end
  true
end

CHANGE_TACTICS_TURN = 12
MAX_MINES = 12
MAX_TOWERS = 5
MAX_LVL1_UNITS = 6
MAX_LVL2_UNITS = 8
MAX_LVL3_UNITS = 3

@graph_map = Graph.new # game map
@frontier = Frontier.new
@units = Units.new
@buildings = Buildings.new
@resources = Resources.new
@mines = Mines.new

@number_mine_spots = gets.to_i
@number_mine_spots.times do
  x, y = gets.split(' ').collect(&:to_i)
  @mines.add_mine(x, y)
end

@current_turn = 1

# game loop
loop do
  map = []
  update_resources

  # Get map
  12.times do
    row = gets.chomp
    map << row
  end
  if @current_turn == 1
    create_graph_map(map)
    construct_graph_map_edges
  else
    update_graph_map(map)
  end
  update_frontiers
  update_buildings
  update_units

  give_order
  @current_turn += 1
end

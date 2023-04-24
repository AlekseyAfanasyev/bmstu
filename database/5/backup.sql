--
-- PostgreSQL database dump
--

-- Dumped from database version 12.13 (Ubuntu 12.13-0ubuntu0.20.04.1)
-- Dumped by pg_dump version 12.13 (Ubuntu 12.13-0ubuntu0.20.04.1)

-- Started on 2023-02-16 10:23:48 MSK

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 212 (class 1259 OID 16573)
-- Name: chess_games; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.chess_games (
    game_id integer NOT NULL,
    format character(50),
    moves text,
    result character(50) NOT NULL,
    time_control character(50),
    game_date date,
    white_id integer NOT NULL,
    black_id integer NOT NULL,
    opening_id character(10) NOT NULL,
    tournament_id integer NOT NULL
);


ALTER TABLE public.chess_games OWNER TO postgres;

--
-- TOC entry 211 (class 1259 OID 16571)
-- Name: chess_games_game_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.chess_games_game_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.chess_games_game_id_seq OWNER TO postgres;

--
-- TOC entry 3030 (class 0 OID 0)
-- Dependencies: 211
-- Name: chess_games_game_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.chess_games_game_id_seq OWNED BY public.chess_games.game_id;


--
-- TOC entry 208 (class 1259 OID 16487)
-- Name: chessplayers; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.chessplayers (
    chessplayer_id integer NOT NULL,
    first_name character(50) NOT NULL,
    last_name character(50) NOT NULL,
    elo_rating integer NOT NULL,
    birth_year integer
);


ALTER TABLE public.chessplayers OWNER TO postgres;

--
-- TOC entry 207 (class 1259 OID 16485)
-- Name: chessplayers_chessplayer_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.chessplayers_chessplayer_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.chessplayers_chessplayer_id_seq OWNER TO postgres;

--
-- TOC entry 3031 (class 0 OID 0)
-- Dependencies: 207
-- Name: chessplayers_chessplayer_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.chessplayers_chessplayer_id_seq OWNED BY public.chessplayers.chessplayer_id;


--
-- TOC entry 206 (class 1259 OID 16479)
-- Name: judges; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.judges (
    judge_id integer NOT NULL,
    first_name character(50) NOT NULL,
    last_name character(50) NOT NULL,
    email character(50)
);


ALTER TABLE public.judges OWNER TO postgres;

--
-- TOC entry 205 (class 1259 OID 16477)
-- Name: judges_judge_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.judges_judge_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.judges_judge_id_seq OWNER TO postgres;

--
-- TOC entry 3032 (class 0 OID 0)
-- Dependencies: 205
-- Name: judges_judge_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.judges_judge_id_seq OWNED BY public.judges.judge_id;


--
-- TOC entry 202 (class 1259 OID 16461)
-- Name: openings; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.openings (
    eco_id character(10) NOT NULL,
    openings_group character(50) NOT NULL,
    name character(250) NOT NULL,
    moves character(250) NOT NULL,
    alternative_names character(250),
    named_after character(250)
);


ALTER TABLE public.openings OWNER TO postgres;

--
-- TOC entry 204 (class 1259 OID 16471)
-- Name: places; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.places (
    place_id integer NOT NULL,
    city character(50),
    country character(50) NOT NULL
);


ALTER TABLE public.places OWNER TO postgres;

--
-- TOC entry 203 (class 1259 OID 16469)
-- Name: places_place_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.places_place_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.places_place_id_seq OWNER TO postgres;

--
-- TOC entry 3033 (class 0 OID 0)
-- Dependencies: 203
-- Name: places_place_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.places_place_id_seq OWNED BY public.places.place_id;


--
-- TOC entry 210 (class 1259 OID 16495)
-- Name: tournaments; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.tournaments (
    tournament_id integer NOT NULL,
    name character(250) NOT NULL,
    rating_restriction integer,
    winner_id integer NOT NULL,
    place_id integer NOT NULL,
    judge_id integer NOT NULL
);


ALTER TABLE public.tournaments OWNER TO postgres;

--
-- TOC entry 209 (class 1259 OID 16493)
-- Name: tournaments_tournament_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.tournaments_tournament_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tournaments_tournament_id_seq OWNER TO postgres;

--
-- TOC entry 3034 (class 0 OID 0)
-- Dependencies: 209
-- Name: tournaments_tournament_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.tournaments_tournament_id_seq OWNED BY public.tournaments.tournament_id;


--
-- TOC entry 2868 (class 2604 OID 16576)
-- Name: chess_games game_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.chess_games ALTER COLUMN game_id SET DEFAULT nextval('public.chess_games_game_id_seq'::regclass);


--
-- TOC entry 2866 (class 2604 OID 16490)
-- Name: chessplayers chessplayer_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.chessplayers ALTER COLUMN chessplayer_id SET DEFAULT nextval('public.chessplayers_chessplayer_id_seq'::regclass);


--
-- TOC entry 2865 (class 2604 OID 16482)
-- Name: judges judge_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.judges ALTER COLUMN judge_id SET DEFAULT nextval('public.judges_judge_id_seq'::regclass);


--
-- TOC entry 2864 (class 2604 OID 16474)
-- Name: places place_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.places ALTER COLUMN place_id SET DEFAULT nextval('public.places_place_id_seq'::regclass);


--
-- TOC entry 2867 (class 2604 OID 16498)
-- Name: tournaments tournament_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tournaments ALTER COLUMN tournament_id SET DEFAULT nextval('public.tournaments_tournament_id_seq'::regclass);


--
-- TOC entry 3024 (class 0 OID 16573)
-- Dependencies: 212
-- Data for Name: chess_games; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.chess_games (game_id, format, moves, result, time_control, game_date, white_id, black_id, opening_id, tournament_id) FROM stdin;
1	Классика                                          	1.d4 Nf6 2.c4 e6 3.Nf3 Bb4+ 4.Bd2 Qe7 5.g3 O-O 6.Bg2 Bxd2+ 7.Qxd2 d6 8.Nc3 c6 9.O-O Nbd7 10.e4 e5 11.Nh4 Nb6 12.b3 Ng4 13.Rad1 Nh6 14.h3 Be6 15.Qe3 Rad8 16.Rd2 Bxc4 17.bxc4 Nxc4 18.Qe2 Nxd2 19.Qxd2 f5 20.exf5 Nxf5 21.Nxf5 Rxf5 22.d5 c5 23.Rb1 Qd7 24.a4 Rdf8 25.Ne4 Qxa4 26.Rxb7 Qa1+ 27.Kh2 Qa4 28.Qe2 Qd4 29.Qg4 g6 30.Rxa7 c4 31.Rc7 Kh8 32.Qh4 R8f7 33.Qd8+ Kg7 34.Nxd6 Rxf2 35.Rxf7+ Rxf7 36.Nxf7 Kxf7 37.d6	0-1                                               	Классика                                          	2003-06-29	1	2	E11       	1
2	Рапид                                             	1.e4 Nc6 2.Nf3 d6 3.d4 Nf6 4.Nc3 g6 5.Bb5 a6 6.Bxc6+ bxc6 7.O-O Bg7 8.Re1 O-O 9.h3 Rb8 10.b3 Bb7 11.e5 Nd5 12.Nxd5 cxd5 13.Bg5 dxe5 14.dxe5 c5 15.c3 Re8 16.Qe2 Qa5 17.Qe3 Rbd8 18.Bh6 Bh8 19.e6 f5 20.Ne5 Rd6 21.Nxg6 hxg6 22.Qg5 Kh7 23.Qh4 Bg7 24.Bf4+ Kg8 25.Bxd6 exd6 26.Qg5 Kh7 27.Qh4+ Bh6 28.Qf6 Qc7 29.e7 Bg7 30.Qf7 Qd7 31.Re6 Kh8 32.Rae1 d4 33.Rxg6 Rg8 34.Rg5	1-0                                               	10-0                                              	2022-05-11	5	7	B00       	8
3	Блиц                                              	1.d4 Nf6 2.Nf3 d5 3.c4 e6 4.Nc3 c6 5.Bg5 Nbd7 6.e3 Qa5 7.Nd2 Bb4 8.Qc2 O-O 9.a3 Ne4 10.Ncxe4 dxe4 11.Bh4 e5 12.O-O-O Bxd2+ 13.Rxd2 exd4 14.Rxd4 f5 15.Be2 Nc5 16.Bg3 Be6 17.Kb1 Qb6 18.Rhd1 a5 19.Rd6 Rfe8 20.Be5 a4 21.Qc3 Re7 22.Bd4 Rc8 23.g4 Rf8 24.gxf5 Bxf5 25.Rg1 Bg6 26.h4 Rxf2 27.Qe1 Rh2 28.Rg5 Qc7 29.Bxc5 b6 30.Rxc6 Qxc6 31.Bxe7 1-0	1-0                                               	3-0                                               	2009-02-05	3	4	D52       	1
4	Классика                                          	1.d4 Nf6 2.c4 e6 3.Nf3 Bb4+ 4.Bd2 Qe7 5.g3 Nc6 6.Nc3 Bxc3 7.Bxc3 Ne4 8.Rc1 O-O 9.Bg2 d6 10.d5 Nxc3 11.Rxc3 Ne5 12.Nd4 Bd7 13.O-O Rfd8 14.f4 Ng6 15.dxe6 fxe6 16.Re3 Nf8 17.Qd2 c6 18.Nf5 1-0	1-0                                               	Классика                                          	2013-09-17	5	1	E11       	2
5	Пуля                                              	1.g4 d5 2.Bg2 c6 3.h3 e5 4.d3 Bc5 5.Nf3 f6 6.Nbd2 Ne7 7.c4 Be6 8.b3 Qb6 9.e3 d4 10.e4 Ng6 11.a3 Nf4 12.Bf1 a5 13.Nh4 h5 14.Nf5 Kf7 15.Rg1 g6 16.Ng3 hxg4 17.hxg4 Nd7 18.Nb1 Rh4 19.f3 Rah8 20.Ra2 Bf8 21.Ne2 Rh2 22.Rb2 Bb4+ 23.axb4 Qxb4+ 24.Nec3 dxc3 25.Rc2 Qxb3 26.Rxh2 Qxd1+ 27.Kxd1 Rxh2 28.Nxc3 g5 29.Bxf4 gxf4 30.Rg2 Rxg2 31.Bxg2 Ke7 32.Kd2 Kd6 33.Bf1 Kc5 34.Be2 Kb4 35.Kc2 Nc5 36.Kb2 Na4+ 37.Nxa4 Kxa4 38.Kc3 b5 39.Bd1+ Ka3 40.cxb5 cxb5 41.d4 b4+ 42.Kd3 exd4 43.Kxd4 b3 44.e5 b2 45.Bc2 fxe5+ 46.Kxe5 Bxg4 0-1	0-1                                               	1-0                                               	2009-02-03	1	3	A00       	3
6	Классика                                          	1.e4 e5 2.Nc3 Nf6 3.Nf3 Nc6 4.d4 exd4 5.Nxd4 Bb4 6.Nxc6 bxc6 7.Bd3 d5 8.exd5 Qe7+ 9.Qe2 Qxe2+ 10.Kxe2 Bxc3 11.bxc3 cxd5 12.f3 Be6 13.Be3 Kd7 14.Rab1 Ne8 15.c4 Nd6 16.Rhd1 dxc4 17.Be4 Rab8 18.c3 Rxb1 19.Bxb1 a6 20.Bc2 Rb8 21.Rd2 Ke7 22.Bc5 Rb5 23.Bd4 Nf5 24.Ba7 Nd6 25.g4 h5 ½-½	1-1                                               	Классика                                          	2007-08-16	4	1	C47       	1
7	Рапид                                             	1.d4 Nf6 2.c4 e6 3.Nf3 Bb4+ 4.Bd2 c5 5.Bxb4 cxb4 6.g3 O-O 7.Bg2 d6 8.O-O Nc6 9.Qb3 Qb6 10.d5 Na5 11.Qd3 Qa6 12.Nfd2 exd5 13.cxd5 Qxd3 14.exd3 Bf5 15.a3 b3 16.Be4 Bxe4 17.dxe4 Rac8 18.Nc3 Nc4 19.Nxc4 Rxc4 20.f3 a6 ½-½	1-1                                               	10-0                                              	2019-08-15	6	1	E11       	2
8	Пуля                                              	1.d4 Nf6 2.Nf3 e6 3.c4 d5 4.Nc3 c6 5.Bg5 Nbd7 6.e3 Qa5 7.Nd2 Bb4 8.Qc2 O-O 9.a3 e5 10.Rc1 Bxc3 11.Qxc3 Qxc3 12.bxc3 Ne4 13.cxd5 Nxg5 14.h4 exd4 15.cxd4 Nb6 16.hxg5 Nxd5 17.Bd3 g6 18.Rh4 f6 19.gxf6 Nxf6 20.Nb3 Bf5 21.Bxf5 gxf5 22.Na5 Rf7 23.Rb1 Rb8 24.Nxc6 Rc8 25.Ne5 Rg7 26.g3 Rc2 27.Rf4 Rgc7 28.Rxf5 Ne4 29.Rf4 Nd6 30.Kf1 R7c3 31.a4 Ra3 32.Rb4 b6 33.d5 1-0	1-1                                               	1-0                                               	1999-12-04	2	3	D52       	3
9	Рапид                                             	1.b3 c5 2.Bb2 Nf6 3.e3 g6 4.Bxf6 exf6 5.c4 Bg7 6.Nc3 O-O 7.g3 Nc6 8.Bg2 Re8 9.Nge2 Ne5 10.d3 d6 11.O-O a6 12.Qd2 Rb8 13.h3 Be6 14.d4 Nxc4 15.bxc4 Bxc4 16.Rfd1 b5 17.Rac1 Qe7 18.Nf4 Qa7 19.h4 h5 20.Bd5 Bxd5 21.Ncxd5 c4 22.Qa5 Rb7 23.Nb4 Ra8 24.Nfd5 g5 25.a4 gxh4 26.gxh4 f5 27.axb5 axb5 28.Qxa7 Rbxa7 29.Rb1 Rb7 30.Nc3 Rab8 31.Ncd5 Kf8 32.Ra1 Ke8 33.Ra6 Kd7 34.Rda1 Rc8 35.Ra7 Rxa7 36.Rxa7+ Ke8 37.Nc3 f4 38.Nxb5 c3 39.Nxd6+ 1-0	1-0                                               	10-0                                              	2003-11-24	4	2	A01       	6
10	Классика                                          	1.d4 Nf6 2.c4 e6 3.Nc3 d5 4.Bg5 c6 5.e3 Nbd7 6.Nf3 Be7 7.Qc2 a6 8.a3 h6 9.Bh4 O-O 10.Bd3 dxc4 11.Bxc4 b5 12.Ba2 c5 13.dxc5 Nxc5 14.Rd1 Qb6 15.Bb1 Rd8 16.Rxd8+ Qxd8 17.O-O Bb7 18.Rd1 Qc7 19.b4 Ncd7 20.Nd5 Qxc2 21.Nxe7+ Kf8 22.Bxc2 Kxe7 23.Nd4 Rc8 24.h3 g5 25.Bg3 Be4 26.Bb3 Rc3 27.f3 Bd5 28.Bxd5 Nxd5 29.e4 Ne3 30.Ra1 e5 31.Nf5+ Nxf5 32.exf5 Kf6 33.Rd1 Ke7 34.Ra1 Kf6 35.Rd1 ½-½	1-1                                               	Классика                                          	2017-04-18	5	2	D52       	6
11	Пуля                                              	1.e4 c5 2.Nf3 Nc6 3.d4 cxd4 4.Nxd4 Qc7 5.Nc3 e6 6.Be3 a6 7.Qd2 Nf6 8.O-O-O b5 9.Bf4 Qb6 10.Nb3 Ng4 11.h3 Nge5 12.Kb1 d6 13.Be3 Qb7 14.Ka1 Rb8 15.Nd4 Bd7 16.f4 Nc4 17.Bxc4 bxc4 18.Rb1 Be7 19.g4 O-O 20.Nde2 Nb4 21.a3 a5 22.Nd4 Bf6 23.g5 Bxd4 24.Bxd4 Bc6 25.Rhe1 Rfe8 26.f5 e5 27.Bf2 d5 28.exd5 Bd7 29.f6 Bf5 30.Rec1 Red8 31.Bg3 Re8 32.fxg7 Rbd8 33.Be1 Nxd5 34.Nxd5 Qxd5 35.Qf2 e4 36.Qe3 Qd4 37.Qf4 Qe5 38.Qxe5 Rxe5 39.Bc3 Red5 40.Re1 e3 41.Re2 Bxh3 42.Rxe3 Be6 43.Bf6 Rc8 44.Rbe1 a4 45.Kb1 Rf5 46.Kc1 Rf4 47.Re4 Rf3 48.Rd4 1-0	1-0                                               	1-0                                               	2017-04-18	6	2	B00       	7
12	Блиц                                              	1.d4 Nf6 2.c4 e6 3.Nf3 d5 4.Nc3 c6 5.Bg5 Nbd7 6.e3 Qa5 7.Nd2 Bb4 8.Qc2 O-O 9.a3 Ne4 10.Ncxe4 dxe4 11.Bh4 g5 12.Bg3 f5 13.f4 exf3 14.gxf3 e5 15.O-O-O Be7 16.Bd3 exd4 17.exd4 Nf6 18.Rhe1 Rf7 19.c5 f4 20.Bf2 Nd5 21.Nc4 Qd8 22.Ne5 Rg7 23.Rg1 Bh3 24.Rde1 Bf6 25.Ng4 Bxg4 26.fxg4 Ne3 27.Bxe3 fxe3 28.Rd1 Kh8 29.Bf5 Qe7 30.Rge1 Qe8 31.Rd3 Re7 32.Qe2 Qf7 33.Rxe3 Rae8 34.Qd3 Rxe3 35.Rxe3 Rxe3 36.Qxe3 Qc4+ 37.Qc3 Qf1+ 38.Kc2 Qf2+ 39.Qd2 Qxd2+ 40.Kxd2 ½-½	1-1                                               	Классика                                          	2017-04-18	3	4	D52       	1
13	Рапид                                             	1.e4 e6 2.d4 d5 3.Nc3 dxe4 4.Nxe4 Nd7 5.Nf3 Ngf6 6.Nxf6+ Nxf6 7.c3 c5 8.Ne5 a6 9.Be3 Qc7 10.Qa4+ Bd7 11.Nxd7 Nxd7 12.Be2 O-O-O 13.O-O Nb6 14.Qa5 Nd5 15.Qxc7+ Kxc7 16.dxc5 Nxe3 17.fxe3 f5 18.b4 g6 19.Bc4 Bg7 20.Rac1 Bh6 21.Rfe1 e5 22.Kf2 Rd2+ 23.Re2 Rhd8 24.Rc2 Rd1 25.e4 Rf8 26.Kg3 Bc1 27.Kh3 f4 28.Rf2 Be3 29.Rf3 h5 30.Kh4 Rfd8 31.Bd5 R8xd5 32.exd5 Rxd5 33.Re2 Rd3 34.Kg5 e4 35.Rfxe3 Rxe3 36.Rf2 f3 37.gxf3 exf3 38.Kxg6 Re2 39.Rxf3 Rg2+ 40.Kh6 Rxh2 41.a4 h4 42.Kh5 a5 43.b5 Ra2 44.Rf7+ Kc8 45.Rf8+ Kd7 46.Rf7+ Kc8 ½-½	1-1                                               	10-0                                              	1999-04-23	4	5	B00       	8
14	Блиц                                              	1.e4 e5 2.Nf3 Nc6 3.Bc4 Bc5 4.d3 Nf6 5.Nc3 h6 6.h3 d6 7.Na4 Bb6 8.a3 Be6 9.Bxe6 fxe6 10.O-O O-O 11.b4 Qe8 12.c3 Kh8 13.Ra2 Qf7 14.Re1 Rad8 15.Nxb6 axb6 16.a4 Ne7 17.a5 Ra8 18.Qb3 bxa5 19.Rxa5 Ng6 20.d4 Nd7 21.Be3 b6 22.Ra2 Rxa2 23.Qxa2 exd4 24.cxd4 Nf6 25.Qc2 Nh5 26.Rc1 Nhf4 27.Ne1 d5 28.Kh2 dxe4 29.Qxe4 Nd5 30.Nd3 Qf5 31.Qxf5 exf5 32.Rc6 Rf6 33.Rxf6 Nxf6 34.Bd2 Kg8 35.f3 Kf7 36.Ne5+ Nxe5 37.dxe5 Nd5 38.f4 Ke6 39.Kg3 Ne7 40.Kf3 Kd5 41.g4 g6 42.Be1 Nc6 43.gxf5 gxf5 44.Ke3 Kc4 45.Ke2 Nd4+ 46.Ke3 Ne6 47.Bd2 Kb3 48.Ke2 Kc2 49.Ke1 c5 50.b5 Kd3 51.Ba5 Kc4 52.Bxb6 Kxb5 53.Ba7 Nxf4 54.Kd2 Kc4 55.Bb8 Kd5 56.h4 h5 57.Ba7 Kd4 58.Bb8 Ne6 59.Kc2 Ke3 60.Kc3 f4 61.Kc4 f3 62.Kd5 Nf4+ 0-1	0-1                                               	3-2                                               	2003-11-25	5	3	C20       	8
15	Пуля                                              	1.e4 e5 2.Nf3 Nc6 3.Bc4 Bc5 4.b4 Bxb4 5.c3 Ba5 6.d4 d6 7.Qb3 Qd7 8.O-O Bb6 9.Nbd2 Na5 10.Qc2 Nxc4 11.Nxc4 Qc6 12.Nxb6 axb6 13.dxe5 dxe5 14.Nxe5 Qa4 15.Qd3 Ne7 16.Qg3 O-O 17.Re1 Be6 18.h4 Kh8 19.h5 h6 20.Bf4 Ra5 21.Rad1 Qxa2 22.Nf3 Rxh5 23.Bxc7 Ng6 24.Bxb6 Kh7 25.Bd4 Re8 26.Ra1 Qc4 27.Ra7 Qc6 28.Raa1 Bd7 29.Nd2 Rg5 30.Qh2 f5 31.Ra5 b5 32.Ra7 fxe4 33.Qc7 Nf8 34.Qxc6 Bxc6 35.Be3 Rd5 36.Rc7 Bd7 37.Ra1 Ne6 38.Rb7 Rd3 39.Raa7 Bc6 40.Re7 Rxe7 41.Rxe7 Bd5 42.Nxe4 Kg6 43.Nd6 Rxc3 44.Nxb5 Rb3 45.Nd4 Nxd4 46.Bxd4 Rb7 47.Rxb7 Bxb7 ½-½	1-1                                               	1-0                                               	2013-09-17	3	6	C20       	7
16	Рапид                                             	1.e4 e5 2.Nf3 Nc6 3.Bb5 a6 4.Ba4 Nf6 5.O-O Be7 6.Re1 b5 7.Bb3 O-O 8.c3 d6 9.h3 Na5 10.Bc2 c5 11.d4 Qc7 12.Nbd2 cxd4 13.cxd4 Nc6 14.a3 exd4 15.Nb3 d3 16.Bxd3 Ne5 17.Bf4 Nxd3 18.Qxd3 Re8 19.Rac1 Qb6 20.Be3 Qb7 21.Bd2 Bd8 22.Qxd6 Bb6 23.Ba5 Bxf2+ 24.Kxf2 Nxe4+ 25.Rxe4 Qxe4 26.Qd2 Qg6 27.Nc5 Bf5 28.Qg5 Qxg5 29.Nxg5 Re5 30.Nf3 Rd5 31.Rc3 h5 32.Kg3 f6 33.Kh2 Kf7 34.Nh4 Bh7 35.Nb3 Re8 36.Bb4 g5 37.Nf3 Be4 38.Rc7+ Kg6 39.Nfd4 Rde5 40.Nc5 Bd5 41.Bc3 h4 42.Nxa6 Re2 43.Nxe2 Rxe2 44.Kg1 Bxg2 45.Nc5 Bxh3 46.Rc6 Rg2+ 47.Kh1 Rf2 48.Rd6 g4 49.Ne4 Rf4 50.Rxf6+ Rxf6 51.Nxf6 g3 52.Nd5 Bd7 53.Kg1 h3 54.Be5 h2+ 55.Kg2 Bc6 ½-½	1-1                                               	5-2                                               	2022-12-22	6	4	B00       	2
17	Классика                                          	1.g4 e5 2.e3 e4 3.b3 d5 4.d3 Qf6 5.dxe4 Qxa1 6.exd5 Qxb1 7.b4 Bxb4+ 0-1	0-1                                               	Классика                                          	2013-09-17	5	6	A00       	2
18	Блиц                                              	1.g4 d5 2.e4 Bf5 3.Qf3 Qd6 4.Qb3 Bc8 5.Qb5+ Kd8 6.Bd3 Na6 7.f4 Nb4 8.Na3 Nxa2 9.e5 Qg6 ½-½	1-1                                               	3-2                                               	2022-12-22	1	2	A00       	7
19	Блиц                                              	1.b3 c5 2.Bb2 Nc6 3.e3 Nf6 4.Nf3 g6 5.Bxf6 exf6 6.c4 Bg7 7.Nc3 O-O 8.g3 f5 9.Bg2 d6 10.O-O Be6 11.Rc1 Ne5 12.d4 Nxf3+ 13.Bxf3 cxd4 14.exd4 Rb8 15.Re1 f4 16.Nd5 fxg3 17.hxg3 h5 18.Qd2 Kh7 19.Rcd1 Bh6 20.Qb4 Kg7 21.a4 b6 22.Kg2 Rc8 23.Qc3 Kg8 24.a5 Bg7 25.axb6 axb6 26.Qb4 Rb8 27.Nf4 Bf5 28.Qb5 Bc2 29.Rd2 Bf5 30.Bc6 h4 31.Rh1 hxg3 32.fxg3 Qe7 33.Re2 Qg5 34.Bd7 Bxd4 35.Bxf5 Qxf5 36.Qxf5 gxf5 37.Nd5 Rfe8 38.Rd2 Be5 39.Rh5 b5 40.cxb5 Rxb5 41.Nc7 Reb8 42.Nxb5 Rxb5 43.Rd3 Kg7 44.Rxf5 Kg6 45.Rf1 f6 46.Kf3 Rb4 47.Rc1 Rb8 48.Rc4 Ra8 49.b4 Ra1 50.Rb3 d5 51.Rc2 d4 52.b5 Rf1+ 53.Kg2 Rd1 54.b6 d3 55.Rc8 Rd2+ 56.Kf3 Rc2 57.Rd8 d2 58.Ke2 Bc3 59.b7 Rc1 60.Rxd2 Bxd2 61.Kxd2 Rg1 62.b8=Q Rg2+ 63.Ke3 Rxg3+ 64.Qxg3+ 1-0	1-0                                               	3-0                                               	2011-11-11	1	3	A01       	3
20	Классика                                          	1.e4 c5 2.Nf3 d6 3.d4 cxd4 4.Nxd4 Nf6 5.Nc3 a6 6.Be3 e6 7.f3 b5 8.g4 h6 9.Qd2 b4 10.Na4 Nbd7 11.O-O-O Ne5 12.b3 d5 13.Bf4 Bd6 14.Bxe5 Bxe5 15.Nc6 Qc7 16.Nxe5 Qxe5 17.Qxb4 dxe4 18.Nb6 Rb8 19.Kb1 Qc7 20.Qa4+ Kf8 21.Nxc8 Rxc8 22.Qc4 Qxc4 23.Bxc4 a5 24.Ba6 Rb8 25.fxe4 h5 26.gxh5 Nxe4 27.Rd4 Nf6 28.Be2 Nxh5 29.Rh4 g6 30.Rg1 Ke7 31.Ra4 Ra8 32.Bf3 Ra7 33.Rg5 f5 34.Rxg6 Kf7 35.Rg2 Nf6 36.Re2 Rh3 37.Bh1 Ng4 38.Kb2 Kf6 39.Bg2 Rxh2 40.Bf3 Rxe2 41.Bxe2 Ne3 42.c4 e5 43.c5 e4 44.b4 Rc7 45.bxa5 Rxc5 46.a6 Nd5 47.a7 Nc7 48.a8=Q Nxa8 49.Rxa8 f4 50.Rf8+ Ke5 51.Bg4 f3 52.Rf5+ Kd4 53.Rxc5 Kxc5 54.Kc3 Kb5 55.Kd2 f2 56.Be2+ Kb4 57.Kc2 Ka3 58.Kb1 e3 59.Ka1 1-0	1-0                                               	Классика                                          	2005-03-30	1	4	B00       	3
21	Классика                                          	1.e4 e5 2.Nf3 Nc6 3.Bc4 Bc5 4.c3 Nf6 5.d3 O-O 6.O-O d5 7.exd5 Nxd5 8.a4 a5 9.Nbd2 Nb6 10.Bb5 Bd6 11.Re1 Bg4 12.Ne4 Na7 13.h3 Bh5 14.d4 Nxb5 15.axb5 exd4 16.Nxd6 Qxd6 17.Qxd4 Qxd4 18.Nxd4 Bg6 19.Bf4 Rfc8 20.Bg3 a4 21.Re7 Nc4 22.Bxc7 Kf8 23.Rae1 Re8 24.Rxe8+ Rxe8 25.Rc1 Nxb2 26.Bd6+ Kg8 27.c4 Re4 28.c5 Rxd4 29.c6 bxc6 30.Rxc6 Rc4 31.Bc5 h6 32.b6 Rc1+ 33.Kh2 Rxc5 34.Rxc5 Be4 35.f3 Bb7 36.Rc7 Bd5 37.b7 Bxb7 38.Rxb7 Nd3 39.Rd7 Nb2 40.Rd2 Nc4 41.Rd4 Nb2 42.Rb4 Nd3 43.Rxa4 g5 44.Kg3 Kg7 45.Rd4 Nc5 46.Rd6 Ne6 47.Kf2 Nf4 48.Rd4 Ne6 49.Rc4 f5 50.g3 Kf6 51.Rb4 Ke5 52.Rb5+ Kf6 53.Rb6 Ke5 54.g4 Kf6 55.Ke3 fxg4 56.hxg4 Ke5 57.Ra6 Kf6 58.Ke4 Kf7 59.Ke5 1-0	1-0                                               	Классика                                          	2017-04-18	2	3	C20       	7
22	Блиц                                              	1.e4 e5 2.Nf3 Nc6 3.Nc3 Nf6 4.d4 exd4 5.Nxd4 Bb4 6.Nxc6 bxc6 7.Bd3 d5 8.exd5 cxd5 9.O-O O-O 10.Bg5 c6 11.Ne2 Re8 12.Nd4 Bd7 13.Qf3 Be7 14.Rfe1 h6 15.Bf4 Qb6 16.Nf5 Bxf5 17.Bxf5 Qxb2 18.Be5 Qa3 19.Re3 Qa5 20.Qg3 d4 21.Re2 Bd6 22.f4 Bxe5 23.fxe5 Nd5 24.e6 fxe6 25.Rxe6 Ne3 26.Bh7+ Kh8 27.Rxe8+ Rxe8 28.Bd3 Qg5 29.Qxg5 hxg5 30.Rb1 c5 31.Bg6 Rf8 32.h3 c4 33.Rb7 d3 34.cxd3 c3 35.d4 c2 36.Bxc2 Nxc2 37.d5 Rd8 38.Rxa7 Rxd5 39.a4 Ne3 40.Kf2 Nc4 41.Kf3 Re5 42.Rc7 Na5 43.Kg4 Kh7 44.Kh5 Nb3 45.Ra7 Nd4 46.Kg4 Kh6 47.Ra6+ g6 48.Ra8 Re4+ 49.Kg3 Re3+ 50.Kf2 Re2+ 51.Kg3 Ra2 52.Rh8+ Kg7 53.Ra8 Nf5+ 54.Kf3 Nh4+ 55.Ke4 Nxg2 56.a5 Nf4 0-1	0-1                                               	3-2                                               	2009-02-03	2	4	C47       	2
23	Классика                                          	1.d4 Nf6 2.c4 e6 3.Nf3 d5 4.Nc3 Nbd7 5.Bg5 c6 6.e3 Qa5 7.Nd2 dxc4 8.Bxf6 Nxf6 9.Nxc4 Qc7 10.Rc1 Be7 11.Be2 O-O 12.O-O Rd8 13.Qb3 Bd7 14.Bf3 Be8 15.Rfd1 Rac8 16.e4 b5 17.Ne3 Qb6 18.e5 Nd7 19.Bg4 Nf8 20.Ne2 Ng6 21.Bh3 c5 22.d5 c4 23.Qc3 Bc5 24.a3 Rb8 25.dxe6 fxe6 26.b4 Be7 27.f4 Nf8 28.Nd4 Bg6 29.Kf2 Bd3 30.Rxd3 cxd3 31.Nc6 Bh4+ 32.g3 d2 33.Rd1 Rbc8 34.Bg2 Rd5 35.Bxd5 exd5 36.Ne7+ Bxe7 37.Qxc8 1-0	1-0                                               	Классика                                          	2017-04-18	2	5	D52       	6
24	Пуля                                              	1.d4 Nf6 2.c4 e6 3.Nf3 Bb4+ 4.Nc3 c5 5.e3 O-O 6.Bd3 d5 7.O-O dxc4 8.Bxc4 Bxc3 9.bxc3 Qc7 10.Bd3 b6 11.Qe2 a5 12.c4 Nbd7 13.e4 e5 14.dxe5 Nxe5 15.Nxe5 Qxe5 16.Bb2 Qh5 17.f3 Nd7 18.Bc2 Ba6 19.e5 Rad8 20.Rad1 Qh4 21.f4 Nb8 22.Qe4 b5 23.e6 fxe6 24.Qxe6+ Kh8 25.Rxd8 Rxd8 26.Qf7 Qh6 27.Re1 1-0	1-0                                               	1-0                                               	2009-02-05	3	4	E11       	6
25	Классика                                          	1.d4 d5 2.Nf3 c6 3.c4 Nf6 4.Nc3 e6 5.Bg5 Nbd7 6.e3 Qa5 7.Nd2 Bb4 8.Qc2 c5 9.Be2 cxd4 10.exd4 dxc4 11.Bxf6 Nxf6 12.Nxc4 Bxc3+ 13.bxc3 Qc7 14.Qa4+ Kf8 15.O-O b6 16.Bf3 Bb7 17.Bxb7 Qxb7 18.Ne3 g6 19.c4 Kg7 20.d5 exd5 21.cxd5 Nxd5 22.Qe4 Rad8 23.Rad1 Rhe8 ½-½	1-1                                               	Классика                                          	2017-04-18	3	5	D52       	7
26	Пуля                                              	1.e4 e5 2.Nf3 Nc6 3.Nc3 Nf6 4.d4 exd4 5.Nxd4 Nxe4 6.Nxe4 Qe7 7.f3 d5 8.Bb5 Bd7 9.O-O dxe4 10.Bxc6 bxc6 11.fxe4 O-O-O 12.Qe2 Re8 13.Qa6+ Kd8 14.Rd1 Qc5 15.Be3 Bd6 16.Ne6+ Rxe6 17.Bxc5 Bxc5+ 18.Kh1 Rhe8 19.b4 Bd6 20.c4 Rh6 21.h3 Rxe4 22.c5 Bxh3 23.Rxd6+ cxd6 24.gxh3 Rxh3+ 25.Kg2 Ree3 26.Qxc6 Rhg3+ 27.Kf2 1-0	1-0                                               	1-0                                               	2013-09-17	3	6	C47       	3
27	Пуля                                              	1.e4 e5 2.Nf3 Nc6 3.Bc4 Nf6 4.d3 Bc5 5.Nc3 h6 6.O-O O-O 7.h3 Re8 8.Be3 Bb6 9.a3 d6 10.Re1 Be6 11.Bxe6 Rxe6 12.Bxb6 axb6 13.d4 exd4 14.Nxd4 Nxd4 15.Qxd4 Qd7 16.Re3 Rae8 17.Rae1 Qc6 18.a4 Qc5 19.Qd3 c6 20.Kf1 h5 21.g3 h4 22.g4 Qe5 23.Kg1 Nd7 24.Qd2 Qf6 25.Qe2 Ne5 26.b3 g5 27.Rd1 Qf4 28.Kg2 Rf6 29.Nb1 Ng6 30.Nd2 Qe5 31.Kg1 Nf4 32.Qf1 Qc5 33.Qc4 d5 34.Qxc5 bxc5 35.exd5 Rxe3 36.fxe3 Nxh3+ 37.Kg2 Nf2 38.Rf1 h3+ 39.Kg3 Ne4+ 40.Kh2 Rxf1 41.Nxf1 cxd5 42.Ng3 Nf2 43.Nf5 Kf8 44.Nd6 b6 45.Nc8 Nxg4+ 46.Kxh3 Nxe3 47.Nxb6 Nxc2 48.Nxd5 Ke8 49.Kg4 Kd7 50.a5 Kc6 51.a6 Nd4 52.b4 c4 53.Ne3 c3 54.Kxg5 ½-½	1-1                                               	1-0                                               	2009-02-01	4	5	C20       	8
28	Рапид                                             	1.e4 e5 2.Nf3 Nc6 3.Bb5 a6 4.Ba4 Nf6 5.O-O Be7 6.Re1 b5 7.Bb3 O-O 8.h3 Bb7 9.d3 d6 10.a4 Na5 11.Ba2 c5 12.Nbd2 Nc6 13.Nf1 Nd7 14.Ne3 Nb6 15.Nf5 Bc8 16.Nxe7+ Qxe7 17.Bg5 Qc7 18.Nh4 Be6 19.Nf5 c4 20.dxc4 Nxc4 21.b3 Nb6 22.c4 bxc4 23.bxc4 Nd7 24.Qxd6 Qxd6 25.Nxd6 Nc5 26.Be3 Nd4 27.Rad1 Rab8 28.Bb1 Nxa4 29.Bxd4 exd4 30.Rxd4 Rb2 31.e5 Nc5 32.Bf5 a5 33.Bxe6 ½-½	0-1                                               	5-0                                               	2013-09-17	4	6	B00       	3
29	Блиц                                              	1.b3 e5 2.Bb2 Nc6 3.e3 d5 4.Nf3 Bd6 5.d4 e4 6.Ne5 Nce7 7.c4 c6 8.c5 Bc7 9.f3 Nf6 10.f4 Nf5 11.Kf2 h5 12.Be2 g6 13.g3 Bxe5 14.dxe5 Ng4+ 15.Bxg4 hxg4 16.e6 Rh7 17.exf7+ Kxf7 18.Na3 Qa5 19.Rc1 Be6 20.Qe1 Qa6 21.Qe2 d4 22.Qxa6 dxe3+ 23.Ke2 bxa6 24.Nc2 Rd8 25.Nxe3 Nxe3 26.Kxe3 Rd3+ 27.Ke2 Bf5 28.Be5 Ke6 29.Bd6 Kd5 30.Rc2 e3 31.Rc4 Be4 32.Ra4 Rb7 33.h4 Rd2+ 34.Kxe3 Rd3+ 35.Ke2 a5 36.Rd1 Rxd1 37.Kxd1 Rb4 38.Rxa5 Rd4+ 39.Ke2 Rd3 40.f5 Bxf5 41.Rxa7 Rc3 42.Kd2 Rf3 43.b4 Kd4 44.Bf4 Rf2+ 45.Ke1 Rb2 46.a3 Bd3 47.Rd7+ Kc3 48.Be5+ 1-0	1-0                                               	3-2                                               	2013-09-17	4	1	A01       	8
30	Пуля                                              	1.g4 g5 2.d4 Bg7 3.Nc3 d5 4.Bxg5 Bxg4 5.Qd3 Nc6 6.O-O-O Qd7 7.Nf3 Nb4 8.Qd2 c5 9.Rg1 Bxf3 10.exf3 cxd4 11.Bb5 Nxa2+ 12.Nxa2 Qxb5 13.Bxe7 Nxe7 14.Rxg7 O-O-O 15.Qxd4 Nc6 16.Qf4 Rd7 17.Rxf7 Rxf7 18.Qxf7 d4 19.Kb1 Qe2 20.Rg1 Re8 21.Nc1 Qe7 22.Qf5+ Qd7 23.Qxd7+ Kxd7 24.Rg7+ Re7 25.Rxe7+ Kxe7 26.Nd3 Ke6 27.Nc5+ Kd5 28.Nxb7 Ne5 29.f4 Ng4 30.h3 Nxf2 31.h4 h5 32.b4 d3 33.Kc1 Ke4 34.Nc5+ Kxf4 35.Nxd3+ Nxd3+ 36.cxd3 Kg4 37.Kd2 Kxh4 38.Ke2 Kg5 39.Kf3 Kf5 40.b5 Ke5 41.Ke3 Kd5 42.d4 h4 0-1	0-1                                               	1-0                                               	2017-04-18	5	6	A00       	6
31	Блиц                                              	1.b3 Nf6 2.Bb2 d5 3.e3 e6 4.Nf3 Be7 5.d4 O-O 6.Bd3 Nbd7 7.Nbd2 b6 8.e4 dxe4 9.Nxe4 Bb7 10.Qe2 Nxe4 11.Bxe4 Bxe4 12.Qxe4 Nf6 13.Qe2 Qd5 14.O-O-O b5 15.Kb1 b4 16.Rhe1 a5 17.Qc4 c6 18.Ne5 Rfc8 19.g4 a4 20.f3 Qb5 21.f4 Nd5 22.f5 exf5 23.Qxb5 cxb5 24.gxf5 Rc7 25.Rd2 Kf8 26.Nd3 Rd8 27.Re4 Bd6 28.Nc5 a3 29.Ba1 Nc3+ 30.Bxc3 bxc3 31.Rd3 Bxc5 32.dxc5 Rxd3 33.cxd3 Rxc5 34.f6 gxf6 35.Kc2 Rh5 36.h4 Rf5 37.Kxc3 Rf2 38.Rb4 Rxa2 39.Rxb5 Ra1 40.Ra5 f5 41.b4 f4 42.Kb3 a2 43.Rd5 Rb1+ 44.Kxa2 Rxb4 45.Ka3 Rb6 46.Rf5 Rd6 47.Rxf4 Rxd3+ 48.Kb4 Kg7 49.Kc4 Rd7 50.Kc5 f6 51.Kc6 Rd1 52.Ra4 Kg6 0-1	0-1                                               	3-0                                               	2003-11-26	5	1	A01       	2
32	Пуля                                              	1.e4 e5 2.Nf3 Nc6 3.Bb5 a6 4.Ba4 d6 5.O-O Bd7 6.c3 g6 7.d4 Bg7 8.Be3 Nf6 9.Nbd2 O-O 10.d5 Ne7 11.Bxd7 Qxd7 12.h3 h6 13.c4 c5 14.Ne1 b5 15.b4 bxc4 16.bxc5 c3 17.Nc4 Nxe4 18.Nb6 Qb5 19.Rb1 Qa5 20.cxd6 Nxd6 21.Nxa8 Rxa8 22.Nc2 Nxd5 ½-½	1-1                                               	1-0                                               	2013-09-17	5	2	B00       	7
33	Классика                                          	1.d4 d5 2.Nf3 Nf6 3.c4 c6 4.Nc3 e6 5.Bg5 Nbd7 6.e3 Qa5 7.cxd5 Nxd5 8.Qd2 Bb4 9.Rc1 h6 10.Bh4 b6 11.a3 Bxc3 12.bxc3 c5 13.c4 Qxd2+ 14.Nxd2 N5f6 15.Be2 Bb7 16.f3 Rc8 17.O-O O-O 18.a4 Rfd8 19.Rfd1 Ba6 20.Bf1 cxd4 21.exd4 e5 22.Nb3 exd4 23.Rxd4 Re8 24.a5 Re3 25.Rb1 bxa5 26.Nxa5 Ra3 27.Be1 Nb6 28.Bd3 g6 29.Bb4 Ra2 30.Bf1 Rc2 31.Bd3 Ra2 32.h4 h5 33.Bf1 Rc2 34.Bd3 Ra2 35.Rd1 Ra4 36.Be1 Re8 37.Bc3 Ra3 38.Bb4 Ra4 39.Bd2 Rc8 40.Bc2 Ra3 41.Bb4 Re3 42.c5 Kg7 43.Bb3 Na8 44.Rd8 Nc7 45.c6 Rxd8 46.Rxd8 Re8 47.Rd2 Re1+ 48.Kh2 Re3 49.Kg1 Bc8 50.Kf2 Re8 51.Bc3 Re7 52.Rd8 Be6 53.Bxe6 fxe6 54.Be5 Ne8 55.Nc4 a5 56.Rd7 Kf8 57.Bxf6 Nxf6 58.c7 Re8 59.Rd8 1-0	1-0                                               	Классика                                          	2017-04-18	6	1	D52       	1
34	Классика                                          	1.d4 Nf6 2.c4 e6 3.Nf3 Bb4+ 4.Bd2 Qe7 5.g3 O-O 6.Bg2 Bxd2+ 7.Qxd2 d6 8.Nc3 Nbd7 9.O-O e5 10.Rad1 Re8 11.h3 a5 12.e4 exd4 13.Nxd4 Nc5 14.Rfe1 Bd7 15.Kh2 Qd8 16.f4 h6 17.e5 dxe5 18.fxe5 Nh7 19.Nb3 Nxb3 20.Qxd7 Qxd7 21.Rxd7 Nc5 22.Rxc7 Rac8 23.Rxc8 Rxc8 24.Rd1 Ng5 25.b3 Kf8 26.Nb5 Nge6 27.Bd5 Ke7 28.Nd6 Rc7 29.Rf1 Kf8 30.a3 Re7 31.b4 Nd3 32.bxa5 Nxe5 33.Nxb7 Nc7 34.Nc5 Nd7 35.Nxd7+ Rxd7 36.Rd1 Ke7 37.Bf3 Rxd1 38.Bxd1 Kd6 39.Bf3 Kc5 40.Bb7 f6 41.Kg2 Kxc4 42.a6 Nb5 43.Kf3 Kc5 44.a4 Na7 45.Ke4 g6 46.g4 Kd6 47.Kd4 f5 48.gxf5 gxf5 49.h4 1-0	1-0                                               	Классика                                          	2009-02-03	6	2	E11       	6
35	Блиц                                              	1.d4 Nf6 2.c4 e6 3.Nf3 Bb4+ 4.Bd2 Qe7 5.g3 Nc6 6.Nc3 Bxc3 7.Bxc3 Ne4 8.Rc1 O-O 9.Bg2 d6 10.d5 Nd8 11.O-O e5 12.c5 f5 13.cxd6 cxd6 14.Nd2 Nxc3 15.Rxc3 Nf7 16.Qb3 e4 17.Rfc1 b6 18.Rc7 Qf6 19.Qc3 Ne5 20.Nc4 Ba6 21.Nxe5 Qxe5 22.Qxe5 dxe5 23.g4 g6 24.gxf5 gxf5 25.R1c3 Rf6 26.Rg3+ Rg6 27.Bh3 Rc8 28.d6 Rxc7 29.dxc7 Bc8 30.f3 e3 31.Kf1 Kf7 32.f4 exf4 33.Rf3 Rh6 34.Bxf5 Bxf5 35.Rxf4 Rf6 36.Kg2 Bc8 37.Ra4 a5 38.Rh4 Kg6 39.b4 Rf2+ 40.Kg3 Rxe2 41.bxa5 bxa5 42.Ra4 Rc2 0-1	0-1                                               	3-2                                               	2022-12-22	6	3	E11       	2
36	Блиц                                              	1.g4 g5 2.d4 Bg7 3.Nc3 d5 4.Bxg5 Bxg4 5.Qd3 Nc6 6.O-O-O Qd7 7.Nf3 Nb4 8.Qd2 c5 9.Rg1 Bxf3 10.exf3 cxd4 11.Bb5 Nxa2+ 12.Nxa2 Qxb5 13.Bxe7 Nxe7 14.Rxg7 O-O-O 15.Qxd4 Nc6 16.Qf4 Rd7 17.Rxf7 Rxf7 18.Qxf7 d4 19.Kb1 Qe2 20.Rg1 Re8 21.Nc1 Qe7 22.Qf5+ Qd7 23.Qxd7+ Kxd7 24.Rg7+ Re7 25.Rxe7+ Kxe7 26.Nd3 Ke6 27.Nc5+ Kd5 28.Nxb7 Ne5 29.f4 Ng4 30.h3 Nxf2 31.h4 h5 32.b4 d3 33.Kc1 Ke4 34.Nc5+ Kxf4 35.Nxd3+ Nxd3+ 36.cxd3 Kg4 37.Kd2 Kxh4 38.Ke2 Kg5 39.Kf3 Kf5 40.b5 Ke5 41.Ke3 Kd5 42.d4 h4 0-1	0-1                                               	3-2                                               	2009-02-03	1	4	A00       	7
\.


--
-- TOC entry 3020 (class 0 OID 16487)
-- Dependencies: 208
-- Data for Name: chessplayers; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.chessplayers (chessplayer_id, first_name, last_name, elo_rating, birth_year) FROM stdin;
1	Никита                                            	Лялько                                            	2200	1945
2	Александр                                         	Калугин                                           	2400	1963
3	Михаил                                            	Головкин                                          	2500	1943
4	Константин                                        	Самойлов                                          	2600	1943
5	Алексей                                           	Афанасьев                                         	2000	2020
6	Мария                                             	Карповец                                          	2300	2002
7	Даниил                                            	Сафронов                                          	2600	1977
8	Александр                                         	Оцел                                              	2931	2003
9	Михаил                                            	Елизаров                                          	1600	1968
10	Релтиг                                            	Фьлода                                            	3129	1901
11	Максим                                            	Шибин                                             	1239	2001
12	Магнус                                            	Карлсен                                           	3010	1989
13	Ханс                                              	Ниман                                             	5500	1976
\.


--
-- TOC entry 3018 (class 0 OID 16479)
-- Dependencies: 206
-- Data for Name: judges; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.judges (judge_id, first_name, last_name, email) FROM stdin;
1	Иван                                              	Иванов                                            	ivanov@mail.ru                                    
2	Вадим                                             	Дзитиев                                           	vadim.shachmatist@chess.com                       
3	Константин                                        	Шибин                                             	physics@chess.com                                 
\.


--
-- TOC entry 3014 (class 0 OID 16461)
-- Dependencies: 202
-- Data for Name: openings; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.openings (eco_id, openings_group, name, moves, alternative_names, named_after) FROM stdin;
A00       	Фланговый                                         	Атака Гроба                                                                                                                                                                                                                                               	1.g2-g4                                                                                                                                                                                                                                                   	Дебют Гроба                                                                                                                                                                                                                                               	Генри Гроба                                                                                                                                                                                                                                               
A01       	Фланговые                                         	Дебют Ларсена                                                                                                                                                                                                                                             	1. b2-b3                                                                                                                                                                                                                                                  	Дебют Нимцовича — Ларсена, Дебют Симагина — Ларсена                                                                                                                                                                                                       	Бента Ларсена                                                                                                                                                                                                                                             
B00       	Полуоткрытые                                      	Дебют Нимцовича                                                                                                                                                                                                                                           	1. e2-e4 Kb8-c6                                                                                                                                                                                                                                           	Дебют Фишера, Литовская защита, Начало Нимцовича                                                                                                                                                                                                          	Арона Нимцовича                                                                                                                                                                                                                                           
C20       	Открытые                                          	Атака Оцела                                                                                                                                                                                                                                               	1. e2-e4 e7-e5 2. Фd1-h5                                                                                                                                                                                                                                  	Атака Парэма                                                                                                                                                                                                                                              	Александра Оцела                                                                                                                                                                                                                                          
C47       	Открытые                                          	Белградский гамбит                                                                                                                                                                                                                                        	1. e2-e4 e7-e5 2. Kg1-f3 Kb8-c6 3. Kb1-c3 Kg8-f6 4.d2-d4 e5:d4 5. Kc3-d5                                                                                                                                                                                  	Дебют четырёх коней                                                                                                                                                                                                                                       	Белграда                                                                                                                                                                                                                                                  
D52       	Закрытые                                          	Кембридж-спрингский вариант                                                                                                                                                                                                                               	1. d2-d4 d7-d5 2. c2-c4 e7-e6 3. Кb1-c3 Кg8-f6 4. Сc1-g5 Кb8-d7 5. e2-e3 c7-c6 6. Кg1-f3 Фd8-a5                                                                                                                                                           	Кембридж-спрингская защита, Кембридж-спрингская система, Атака Пильсбери, Защита Пильсбери                                                                                                                                                                	Кембридж-спрингского турнира 1904 года                                                                                                                                                                                                                    
E11       	Полузакрытые                                      	Защита Боголюбова                                                                                                                                                                                                                                         	1. d2-d4 Kg8-f6 2. c2-c4 e7-e6 3. Kg1-f3 Cf8-b4+                                                                                                                                                                                                          	-                                                                                                                                                                                                                                                         	Ефима Боголюбова                                                                                                                                                                                                                                          
\.


--
-- TOC entry 3016 (class 0 OID 16471)
-- Dependencies: 204
-- Data for Name: places; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.places (place_id, city, country) FROM stdin;
1	Любляна                                           	Словения                                          
2	Нью-Йорк                                          	США                                               
3	Париж                                             	Франция                                           
4	Cap dAgde                                         	Франция                                           
\.


--
-- TOC entry 3022 (class 0 OID 16495)
-- Dependencies: 210
-- Data for Name: tournaments; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.tournaments (tournament_id, name, rating_restriction, winner_id, place_id, judge_id) FROM stdin;
1	Ljubljana op 14th                                                                                                                                                                                                                                         	1000	1	1	1
2	CapExpress Poule B 2022                                                                                                                                                                                                                                   	2000	6	4	2
3	Chess Tour De France                                                                                                                                                                                                                                      	1600	3	2	3
4	Russia Cup                                                                                                                                                                                                                                                	1000	4	3	1
5	StellChampionship                                                                                                                                                                                                                                         	500	5	1	2
6	World Cup 2007                                                                                                                                                                                                                                            	1000	5	2	3
7	Lyublyana Op 12                                                                                                                                                                                                                                           	500	5	1	2
8	World Cup 2003                                                                                                                                                                                                                                            	1000	5	2	3
\.


--
-- TOC entry 3035 (class 0 OID 0)
-- Dependencies: 211
-- Name: chess_games_game_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.chess_games_game_id_seq', 36, true);


--
-- TOC entry 3036 (class 0 OID 0)
-- Dependencies: 207
-- Name: chessplayers_chessplayer_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.chessplayers_chessplayer_id_seq', 12, true);


--
-- TOC entry 3037 (class 0 OID 0)
-- Dependencies: 205
-- Name: judges_judge_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.judges_judge_id_seq', 3, true);


--
-- TOC entry 3038 (class 0 OID 0)
-- Dependencies: 203
-- Name: places_place_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.places_place_id_seq', 4, true);


--
-- TOC entry 3039 (class 0 OID 0)
-- Dependencies: 209
-- Name: tournaments_tournament_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.tournaments_tournament_id_seq', 8, true);


--
-- TOC entry 2880 (class 2606 OID 16581)
-- Name: chess_games chess_games_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.chess_games
    ADD CONSTRAINT chess_games_pkey PRIMARY KEY (game_id);


--
-- TOC entry 2876 (class 2606 OID 16492)
-- Name: chessplayers chessplayers_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.chessplayers
    ADD CONSTRAINT chessplayers_pkey PRIMARY KEY (chessplayer_id);


--
-- TOC entry 2874 (class 2606 OID 16484)
-- Name: judges judges_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.judges
    ADD CONSTRAINT judges_pkey PRIMARY KEY (judge_id);


--
-- TOC entry 2870 (class 2606 OID 16468)
-- Name: openings openings_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.openings
    ADD CONSTRAINT openings_pkey PRIMARY KEY (eco_id);


--
-- TOC entry 2872 (class 2606 OID 16476)
-- Name: places places_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.places
    ADD CONSTRAINT places_pkey PRIMARY KEY (place_id);


--
-- TOC entry 2878 (class 2606 OID 16500)
-- Name: tournaments tournaments_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tournaments
    ADD CONSTRAINT tournaments_pkey PRIMARY KEY (tournament_id);


--
-- TOC entry 2884 (class 2606 OID 16582)
-- Name: chess_games chess_games_black_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.chess_games
    ADD CONSTRAINT chess_games_black_id_fkey FOREIGN KEY (black_id) REFERENCES public.chessplayers(chessplayer_id);


--
-- TOC entry 2885 (class 2606 OID 16587)
-- Name: chess_games chess_games_opening_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.chess_games
    ADD CONSTRAINT chess_games_opening_id_fkey FOREIGN KEY (opening_id) REFERENCES public.openings(eco_id);


--
-- TOC entry 2886 (class 2606 OID 16592)
-- Name: chess_games chess_games_tournament_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.chess_games
    ADD CONSTRAINT chess_games_tournament_id_fkey FOREIGN KEY (tournament_id) REFERENCES public.tournaments(tournament_id);


--
-- TOC entry 2887 (class 2606 OID 16597)
-- Name: chess_games chess_games_white_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.chess_games
    ADD CONSTRAINT chess_games_white_id_fkey FOREIGN KEY (white_id) REFERENCES public.chessplayers(chessplayer_id);


--
-- TOC entry 2883 (class 2606 OID 16511)
-- Name: tournaments tournaments_judge_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tournaments
    ADD CONSTRAINT tournaments_judge_id_fkey FOREIGN KEY (judge_id) REFERENCES public.judges(judge_id);


--
-- TOC entry 2882 (class 2606 OID 16506)
-- Name: tournaments tournaments_place_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tournaments
    ADD CONSTRAINT tournaments_place_id_fkey FOREIGN KEY (place_id) REFERENCES public.places(place_id);


--
-- TOC entry 2881 (class 2606 OID 16501)
-- Name: tournaments tournaments_winner_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tournaments
    ADD CONSTRAINT tournaments_winner_id_fkey FOREIGN KEY (winner_id) REFERENCES public.chessplayers(chessplayer_id);


-- Completed on 2023-02-16 10:23:48 MSK

--
-- PostgreSQL database dump complete
--


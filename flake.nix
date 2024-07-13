{
  description = "Agda is a dependently typed programming language / interactive theorem prover.";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
  inputs.flake-parts.url = "github:hercules-ci/flake-parts";

  outputs = inputs: inputs.flake-parts.lib.mkFlake { inherit inputs; } {
    # Support all the OSes
    systems = [ "x86_64-linux" "aarch64-linux" "aarch64-darwin" "x86_64-darwin" ];
    perSystem = { pkgs, ... }: let

      romp-pkg = pkgs.stdenv.mkDerivation {
          name = "romp";
          src = ./.;
          nativeBuildInputs = with pkgs; [ cmake python3 flex bison gmp ];
          nativeCheckInputs = with pkgs; [ lit ];
          doCheck = true;
        };

      # Development environment with tools for hacking on romp
      romp-dev-shell = pkgs.mkShell {
          inputsFrom = [ romp-pkg ];
        };

    in {
      packages.default = romp-pkg;        # Entry point for `nix build`
      devShells.default = romp-dev-shell; # Entry point for `nix develop`
    };
  };
}
